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

    std::string endEffectorTaskPortName = clientComs->getTaskPortName("cartEndEffector");

    ocra_recipes::TRAJECTORY_TYPE trajType = ocra_recipes::MIN_JERK;

    waypoints.resize(3,1);
    waypoints <<    0.33,
                    -0.06,
                    0.65;

    ocra_recipes::TERMINATION_STRATEGY termStrategy = ocra_recipes::BACK_AND_FORTH;

    endEffectorThread = std::make_shared<ocra_recipes::TrajectoryThread>(10, endEffectorTaskPortName, waypoints, trajType, termStrategy);

    // endEffectorThread->setDisplacement(0.2);
    endEffectorThread->setGoalErrorThreshold(0.05);
    endEffectorThread->setMaxVelocity(0.1);

    bool done=false;

    p1 = true;
    p2 = true;
    p3 = true;

    std::cout << "Thread started." << std::endl;
    return true;
}

void ExampleClient::release()
{
    /* Do nothing. */
}

void ExampleClient::loop()
{
    if((yarp::os::Time::now() - startTime) > 5.0 && !done)
    {
        if(trigger){
            endEffectorThread->start();
            trigger = false;
        }

        // if ((yarp::os::Time::now()-startTime)>10.0){
        //     if(p1){
        //         p1=false;
        //         std::cout << "Changing to BACK_AND_FORTH mode:" << std::endl;
        //         endEffectorThread->setTerminationStrategy(ocra_recipes::BACK_AND_FORTH);
        //     }
        //     if ((yarp::os::Time::now()-startTime)>20.0){
        //         if(p2){
        //             p2=false;
        //             std::cout << "Changing to STOP_THREAD mode:" << std::endl;
        //             endEffectorThread->setTerminationStrategy(ocra_recipes::STOP_THREAD);
        //         }
        //         if ((yarp::os::Time::now()-startTime)>30.0){
        //             if(p3){
        //                 p3=false;
        //                 std::cout << "Finished while loop!" << std::endl;
        //                 std::cout << "Stopping thread..." << std::endl;
        //                 endEffectorThread->stop();
        //                 done=true;
        //             }
        //         }
        //     }
        // }
    }

}
