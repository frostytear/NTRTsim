/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 *
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

/**
 * @file App6BarMini.cpp
 * @brief Contains the definition function main() for App6BarMini
 * which builds a 6 bar tensegrity structure defined in YAML or through tgCreator
 * @author Edward Zhu
 * $Id$
 */

// This application
// For yaml model builder
//#include "../../../yamlbuilder/TensegrityModel.h"
// For tgCreator
#include "models/sixBarMiniModel.h"
// This library
#include "core/terrain/tgBoxGround.h"
#include "core/terrain/tgImportGround.h"
#include "core/tgModel.h"
#include "core/tgSimulation.h"
#include "core/tgSimViewGraphics.h"
#include "core/tgWorld.h"
// Bullet Physics
#include "LinearMath/btVector3.h"
// The C++ Standard Library
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
// Controller
#include "controllers/T6MiniRollingController.h"

// #define PI 3.14159

/**
 * The entry point.
 * @param[in] argc the number of command-line arguments
 * @param[in] argv argv[0] is the executable name
 * @param[in] argv argv[1] is the path of the YAML encoded structure
 * @return 0
 */
int main(int argc, char** argv)
{
    // create the ground and world. Specify ground rotation in radians
    const double yaw = 0.0;
    const double pitch =0.0*M_PI/180;
    const double roll = 0.0*M_PI/180;

    double sf = 10;

    // [0, 0.1, 0] rad works
    // [0, 0.15, 0] rad works
    // [0, 0.2, 0] rad works

    // 0.26 rad ~= 15 deg

    // Import Ground
    // ---------------------------------------------------------------------------------
    // Set ground parameters
    btVector3 orientation = btVector3(yaw, pitch, roll);
    const double friction = 1;
    const double restitution = 0.0;
    btVector3 origin = btVector3(0.0, 0.0, 0.0);
    const double margin = 0.05;
    const double offset = 0.5;
    const double scalingFactor = 0.1;
    // const double scalingFactor = sf*1000;
    const int interp = 0;
    const bool twoLayer = false;
    const bool flipXZ = false;

    // Configure ground characteristics
    const tgImportGround::Config groundConfig(orientation, friction, restitution,
        origin, margin, offset, scalingFactor, interp, twoLayer, flipXZ);

    // Get filename from argv
    std::string filename_in = argv[1];
    // std::string filename_in = "../STLParser/rampstls/10degRamp.txt";

    // Check filename
    if (filename_in.find(".txt") == std::string::npos) {
        std::cout << "Incorrect filetype, input file should be a .txt file" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Create filestream
    std::fstream file_in;

    // Open filestream
    file_in.open(filename_in.c_str(), std::fstream::in);

    // Check if input file opened successfully
    if (!file_in.is_open()) {
        std::cout << "Failed to open input file" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "Input file opened successfully" << std::endl;
    }
    tgImportGround* ground = new tgImportGround(groundConfig, file_in);
    // ---------------------------------------------------------------------------------

    // Box ground
    // ---------------------------------------------------------------------------------
    // double frictionCoeff = 1;
    // const tgBoxGround::Config groundConfig(btVector3(yaw, pitch, roll), frictionCoeff);
    // tgBoxGround* ground = new tgBoxGround(groundConfig);
    // ---------------------------------------------------------------------------------


    double gravity = 9.81*sf;
    const tgWorld::Config config(gravity); // gravity, dm/sec^2
    tgWorld world(config, ground);

    // create the view
    const double timestep_physics = 0.0001; // seconds
    const double timestep_graphics = 1.f/60.f; // seconds
    tgSimViewGraphics view(world, timestep_physics, timestep_graphics);

    // create the simulation
    tgSimulation simulation(view);

    // create the models with their controllers and add the models to the simulation
    // Use yaml model builder
    //TensegrityModel* const myModel = new TensegrityModel(argv[1]);

    // Use tgCreator
    sixBarMiniModel* const myModel = new sixBarMiniModel();

    // Define path for controller
    int *pathPtr;
    int path[] = {2, 15, 13, 0, 5, 7, 10}; // Repeat unit is [15, 13, 0, 5, 7, 10]
    int pathSize = sizeof(path)/sizeof(int);
    pathPtr = path;

    // Configure the controlller
    const T6MiniRollingController::Config controllerConfig(gravity, "mini");
    // const T6MiniRollingController::Config controllerConfig(gravity, "dr", btVector3(50, 0, 0));
    // const T6MiniRollingController::Config controllerConfig(gravity, "path", pathPtr, pathSize);

    // Create the controller
    //tensionSensor* const tension_sensor = new tensionSensor();
    T6MiniRollingController* const rollingController = new T6MiniRollingController(controllerConfig);

    // Attach controller to the model
    myModel->attach(rollingController);

    // Add the model to the world
    simulation.addModel(myModel);

    // Run the simulation
    simulation.run();

    // teardown is handled by delete
    return 0;
}