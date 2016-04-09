#include "example-client/ExampleClient.h"

ExampleClient::ExampleClient(std::shared_ptr<ocra::Model> modelPtr, const int loopPeriod)
: ocra_recipes::ControllerClient(modelPtr, loopPeriod)
{
    // poopoo
}

ExampleClient::~ExampleClient()
{
    //caca
}

bool ExampleClient::initialize()
{
    // Set the waypoints w.r.t. the LWR root link frame.
    waypoints.resize(3,4);
    waypoints <<     0.33,  0.0 , -0.1 , -0.40,
                    -0.06, -0.2 , -0.5, -0.20,
                     0.65, 0.75 , 0.4 , 0.35;

    // Pick a termination strategy for the trajectory, i.e. what should the robot do when it reaches the last waypoint of its trajectory?
    // ocra_recipes::TERMINATION_STRATEGY termStrategy = ocra_recipes::BACK_AND_FORTH; // go back and forth from begining to end waypoint
    ocra_recipes::TERMINATION_STRATEGY termStrategy = ocra_recipes::CYCLE; // cycle through the waypoints.
    
    // Type of trajectory to generate.
    ocra_recipes::TRAJECTORY_TYPE trajType = ocra_recipes::MIN_JERK;
    
    int trajectoryUpdatePeriod = 10; // (ms)
    std::string nameOfTheTaskToControl = "cartEndEffector";
    
    endEffectorThread = std::make_shared<ocra_recipes::TrajectoryThread>(trajectoryUpdatePeriod, nameOfTheTaskToControl, waypoints, trajType, termStrategy);

    endEffectorThread->setGoalErrorThreshold(0.01); // This is the acceptable total error between the task frame and the final waypoint. (m)
    endEffectorThread->setMaxVelocity(0.45); // The maximum acceptable velocity between two waypoints. (m/s)

    startTime = yarp::os::Time::now();
    trigger = true;

    std::cout << "Thread started." << std::endl;
    return true;
}

void ExampleClient::release()
{
    /* Do nothing. */
}

void ExampleClient::loop()
{
    if((yarp::os::Time::now() - startTime) > 1.0)
    {
        if(trigger){
            std::cout << "Begining trajectory!" << std::endl;
            endEffectorThread->start();
            trigger = false;
        }
    }

}
