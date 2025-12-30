#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

// Simox Includes
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/XML/RobotIO.h>

// Visualization
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualization.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualizationFactory.h>
#include <VirtualRobot/Visualization/VisualizationFactory.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>

// Coin3D
#include <Inventor/SoDB.h>
#include <Inventor/SoOffscreenRenderer.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>

// SoQt (Still useful for context init, though we won't show window)
#include <Inventor/Qt/SoQt.h>

int main(int argc, char *argv[]) {
  // 1. Initialize
  QWidget *mainWin = SoQt::init("Simox Offscreen");
  if (!mainWin)
    return -1;

  VirtualRobot::init(argc, argv, "SimoxViewer");

  std::cout << "--- Simox Offscreen Rendering ---" << std::endl;

  // 2. Setup Data Paths
  const char *home_env = std::getenv("HOME");
  std::string home_dir = home_env ? home_env : "/tmp";
  std::string dataPath = home_dir + "/grasp_planner/grasp_test_files/";
  VirtualRobot::RuntimeEnvironment::addDataPath(dataPath);
  VirtualRobot::RuntimeEnvironment::addDataPath(dataPath + "objects/");

  // 3. Load Robot
  VirtualRobot::RobotPtr robot;
  try {
    robot =
        VirtualRobot::RobotIO::loadRobot(dataPath + "ArmarIII-RightArm.xml");
    if (robot)
      std::cout << "Robot Loaded." << std::endl;
  } catch (...) {
    std::cerr << "Robot Load Failed." << std::endl;
  }

  // 4. Load Object
  VirtualRobot::ManipulationObjectPtr object;
  try {
    object = VirtualRobot::ObjectIO::loadManipulationObject(
        dataPath + "objects/WaterBottle.xml");
    if (object)
      std::cout << "Object Loaded." << std::endl;
  } catch (...) {
    std::cerr << "Object Load Failed." << std::endl;
  }

  // 5. Build Scene
  SoSeparator *root = new SoSeparator();
  root->ref();

  root->addChild(new SoDirectionalLight);

  // Camera
  SoPerspectiveCamera *cam = new SoPerspectiveCamera;
  cam->position.setValue(1000, 500, 1000);
  cam->pointAt(SbVec3f(0, 0, 0));
  root->addChild(cam);

  // Grid/Axes
  root->addChild(
      VirtualRobot::CoinVisualizationFactory::CreateCoordSystemVisualization());

  if (robot) {
    auto visuBase = robot->getVisualization(VirtualRobot::SceneObject::Full);
    auto robotVisu =
        std::dynamic_pointer_cast<VirtualRobot::CoinVisualization>(visuBase);
    if (robotVisu)
      root->addChild(robotVisu->getCoinVisualization());
  }

  if (object) {
    SoSeparator *sep = new SoSeparator();
    SoTranslation *tr = new SoTranslation();
    tr->translation.setValue(200, 0, 200);
    sep->addChild(tr);

    auto visuBase = object->getVisualization(VirtualRobot::SceneObject::Full);
    auto objVisu =
        std::dynamic_pointer_cast<VirtualRobot::CoinVisualization>(visuBase);
    if (objVisu)
      sep->addChild(objVisu->getCoinVisualization());
    root->addChild(sep);
  }

  // 6. Render
  SoOffscreenRenderer renderer(SbViewportRegion(800, 600));
  renderer.setBackgroundColor(SbColor(0.5, 0.5, 0.5));

  // Fit camera
  cam->viewAll(root, SbViewportRegion(800, 600));

  std::cout << "Rendering..." << std::endl;
  if (renderer.render(root)) {
    // Save as RGB (SGI format, widely readable by tools or ImageMagick)
    if (renderer.writeToRGB("simox_scene.rgb")) {
      std::cout << "Success! Saved to 'simox_scene.rgb'" << std::endl;
    } else {
      std::cerr << "Failed to write file." << std::endl;
    }
  } else {
    std::cerr << "Offscreen Render FAIL." << std::endl;
  }

  root->unref();
  return 0;
}