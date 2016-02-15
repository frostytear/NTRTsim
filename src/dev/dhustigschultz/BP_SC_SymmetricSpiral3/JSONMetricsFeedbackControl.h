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

#ifndef JSON_METRICS_FEEDBACK_CONTROL_H
#define JSON_METRICS_FEEDBACK_CONTROL_H

/**
 * @file JSONStatsFeedbackControl.h
 * @brief A controller for the template class BaseSpineModelLearning
 * @Includes more metrics, such as center of mass of entire structure.
 * @author Brian Mirletz, Dawn Hustig-Schultz
 * @version 1.1.0
 * $Id$
 */

#include "dev/dhustigschultz/BP_SC_NoLegs_Stats/JSONQuadCPGControl.h"

#include <json/value.h>

// Forward Declarations
class neuralNetwork;
class tgSpringCableActuator;

/**
 * JSONMetricsFeedbackControl learns the parameters for a CPG system on a
 * spine like tensegrity structure specified as a BaseSpineModelLearning. Parameters are generated by
 * AnnealEvolution and used in the CPGEquations family of classes.
 * tgImpedanceController controllers are used for the detailed muscle control.
 * Due to the number of parameters, the learned parameters are split
 * into one config file for the nodes and another for the CPG's "edges"
 */
class JSONMetricsFeedbackControl : public JSONQuadCPGControl
{
public:

struct Config : public JSONQuadCPGControl::Config
    {
    public:
        /**
         * The only constructor. 
         */
        Config( int ss,
        int tm,
        int om,
        int param,
        int segnum = 6,
        double ct = 0.1,
        double la = 0,
        double ha = 30,
        double lp = -1 * M_PI,
        double hp = M_PI,
        double kt = 0.0,
        double kp = 1000.0,
        double kv = 100.0,
        bool def = true,
        double cl = 10.0,
        double lf = 0.0,
        double hf = 30.0,
        double ffMin = 0.0,
        double ffMax = 0.0,
        double afMin = 0.0,
        double afMax = 0.0,
        double pfMin = 0.0,
        double pfMax = 0.0,
	double maxH = 60.0, //May need to tune this value more
	double minH = 1.0   //Perhaps same
        );
        
        const double freqFeedbackMin;
        const double freqFeedbackMax;
        const double ampFeedbackMin;
        const double ampFeedbackMax;
        const double phaseFeedbackMin;
        const double phaseFeedbackMax;

	const double maxHeight;
	const double minHeight;
        
        // Values to be filled in by JSON file during onSetup
        int numStates;
        int numActions;
        
    };

    JSONMetricsFeedbackControl(JSONMetricsFeedbackControl::Config config,	
							std::string args,
							std::string resourcePath = "");
    
    virtual ~JSONMetricsFeedbackControl();
    
    virtual void onSetup(BaseQuadModelLearning& subject);
    
    virtual void onStep(BaseQuadModelLearning& subject, double dt);
    
    virtual void onTeardown(BaseQuadModelLearning& subject);
	
protected:

    virtual void setupCPGs(BaseQuadModelLearning& subject, array_2D nodeActions, array_4D edgeActions);
    
    virtual array_2D scaleNodeActions (Json::Value actions);
    
    std::vector<double> getFeedback(BaseQuadModelLearning& subject);
    
    std::vector<double> getCableState(const tgSpringCableActuator& cable);
    
    std::vector<double> transformFeedbackActions(std::vector< std::vector<double> >& actions);

    virtual void printMetrics();
    
    JSONMetricsFeedbackControl::Config m_config;

    std::vector<tgCPGActuatorControl*> m_spineControllers;
    
    // @todo generalize this if we need more than one
    neuralNetwork* nn;

    //One vector for each muscle in the controller, so can save metrics from onStep(), and then print to console at the end (will be redirected into a file in a way that is more easily useable as a .csv file. Names are arbitrary numbers for now, later can make them into more biological-sounding analogs.
    std::vector<double> m_muscleTensionZero;
    std::vector<double> m_muscleTensionOne;
    std::vector<double> m_muscleTensionTwo;
    std::vector<double> m_muscleTensionThree;
    std::vector<double> m_muscleTensionFour;
    std::vector<double> m_muscleTensionFive;
    std::vector<double> m_muscleTensionSix;
    std::vector<double> m_muscleTensionSeven;
    std::vector<double> m_muscleTensionEight;
    std::vector<double> m_muscleTensionNine;
    std::vector<double> m_muscleTensionTen;
    std::vector<double> m_muscleTensionEleven;
    std::vector<double> m_muscleTensionTwelve;
    std::vector<double> m_muscleTensionThirteen;
    std::vector<double> m_muscleTensionFourteen;
    std::vector<double> m_muscleTensionFifteen;
    std::vector<double> m_muscleTensionSixteen;
    std::vector<double> m_muscleTensionSeventeen;
    std::vector<double> m_muscleTensionEighteen;
    std::vector<double> m_muscleTensionNineteen;
    std::vector<double> m_muscleTensionTwenty;
    std::vector<double> m_muscleTensionTwentyOne;
    std::vector<double> m_muscleTensionTwentyTwo;
    std::vector<double> m_muscleTensionTwentyThree;
    std::vector<double> m_muscleTensionTwentyFour;
    std::vector<double> m_muscleTensionTwentyFive;
    std::vector<double> m_muscleTensionTwentySix;
    std::vector<double> m_muscleTensionTwentySeven;
    std::vector<double> m_muscleTensionTwentyEight;
    std::vector<double> m_muscleTensionTwentyNine;
    std::vector<double> m_muscleTensionThirty;
    std::vector<double> m_muscleTensionThirtyOne;
    std::vector<double> m_muscleTensionThirtyTwo;
    std::vector<double> m_muscleTensionThirtyThree;
    std::vector<double> m_muscleTensionThirtyFour;
    std::vector<double> m_muscleTensionThirtyFive;
    std::vector<double> m_muscleTensionThirtySix;
    std::vector<double> m_muscleTensionThirtySeven;
    std::vector<double> m_muscleTensionThirtyEight;
    std::vector<double> m_muscleTensionThirtyNine;
    std::vector<double> m_muscleTensionForty;
    std::vector<double> m_muscleTensionFortyOne;
    std::vector<double> m_muscleTensionFortyTwo;
    std::vector<double> m_muscleTensionFortyThree;
    std::vector<double> m_muscleTensionFortyFour;
    std::vector<double> m_muscleTensionFortyFive;
    std::vector<double> m_muscleTensionFortySix;
    std::vector<double> m_muscleTensionFortySeven;
    std::vector<double> m_muscleTensionFortyEight;
    std::vector<double> m_muscleTensionFortyNine;
    std::vector<double> m_muscleTensionFifty;
    std::vector<double> m_muscleTensionFiftyOne;


    //Vectors for muscle length:
    std::vector<double> m_muscleLengthZero;
    std::vector<double> m_muscleLengthOne;
    std::vector<double> m_muscleLengthTwo;
    std::vector<double> m_muscleLengthThree;
    std::vector<double> m_muscleLengthFour;
    std::vector<double> m_muscleLengthFive;
    std::vector<double> m_muscleLengthSix;
    std::vector<double> m_muscleLengthSeven;
    std::vector<double> m_muscleLengthEight;
    std::vector<double> m_muscleLengthNine;
    std::vector<double> m_muscleLengthTen;
    std::vector<double> m_muscleLengthEleven;
    std::vector<double> m_muscleLengthTwelve;
    std::vector<double> m_muscleLengthThirteen;
    std::vector<double> m_muscleLengthFourteen;
    std::vector<double> m_muscleLengthFifteen;
    std::vector<double> m_muscleLengthSixteen;
    std::vector<double> m_muscleLengthSeventeen;
    std::vector<double> m_muscleLengthEighteen;
    std::vector<double> m_muscleLengthNineteen;
    std::vector<double> m_muscleLengthTwenty;
    std::vector<double> m_muscleLengthTwentyOne;
    std::vector<double> m_muscleLengthTwentyTwo;
    std::vector<double> m_muscleLengthTwentyThree;
    std::vector<double> m_muscleLengthTwentyFour;
    std::vector<double> m_muscleLengthTwentyFive;
    std::vector<double> m_muscleLengthTwentySix;
    std::vector<double> m_muscleLengthTwentySeven;
    std::vector<double> m_muscleLengthTwentyEight;
    std::vector<double> m_muscleLengthTwentyNine;
    std::vector<double> m_muscleLengthThirty;
    std::vector<double> m_muscleLengthThirtyOne;
    std::vector<double> m_muscleLengthThirtyTwo;
    std::vector<double> m_muscleLengthThirtyThree;
    std::vector<double> m_muscleLengthThirtyFour;
    std::vector<double> m_muscleLengthThirtyFive;
    std::vector<double> m_muscleLengthThirtySix;
    std::vector<double> m_muscleLengthThirtySeven;
    std::vector<double> m_muscleLengthThirtyEight;
    std::vector<double> m_muscleLengthThirtyNine;
    std::vector<double> m_muscleLengthForty;
    std::vector<double> m_muscleLengthFortyOne;
    std::vector<double> m_muscleLengthFortyTwo;
    std::vector<double> m_muscleLengthFortyThree;
    std::vector<double> m_muscleLengthFortyFour;
    std::vector<double> m_muscleLengthFortyFive;
    std::vector<double> m_muscleLengthFortySix;
    std::vector<double> m_muscleLengthFortySeven;
    std::vector<double> m_muscleLengthFortyEight;
    std::vector<double> m_muscleLengthFortyNine;
    std::vector<double> m_muscleLengthFifty;
    std::vector<double> m_muscleLengthFiftyOne;

    std::vector< std::vector<double> > m_quadCOM;
    std::vector<double> m_timeStep;

    std::vector<double> m_tensions;
    std::vector<double> m_lengths;
};

#endif // JSON_METRICS_FEEDBACK_CONTROL_H
