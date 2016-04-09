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
    startTime = yarp::os::Time::now();
    trigger = true;

    ocra_recipes::TRAJECTORY_TYPE trajType = ocra_recipes::MIN_JERK;

    waypoints.resize(3,4);
    waypoints <<     0.33,  0.0 , -0.1 , -0.40,
                    -0.06, -0.2 , -0.5, -0.20,
                     0.65, 0.75 , 0.4 , 0.35;

    // Pick between the two different modes.
    // ocra_recipes::TERMINATION_STRATEGY termStrategy = ocra_recipes::BACK_AND_FORTH;
    ocra_recipes::TERMINATION_STRATEGY termStrategy = ocra_recipes::CYCLE;


    endEffectorThread = std::make_shared<ocra_recipes::TrajectoryThread>(10, "cartEndEffector", waypoints, trajType, termStrategy);

    endEffectorThread->setGoalErrorThreshold(0.01);
    endEffectorThread->setMaxVelocity(0.45);

    std::cout << "Thread started." << std::endl;
    return true;
}

void ExampleClient::release()
{
    /* Do nothing. */
}

void ExampleClient::loop()
{
    if((yarp::os::Time::now() - startTime) > 1.0 && !done)
    {
        if(trigger){
            endEffectorThread->start();
            trigger = false;
        }
    }

}
