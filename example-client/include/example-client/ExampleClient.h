#ifndef EXAMPLE_CLIENT_H
#define EXAMPLE_CLIENT_H

#include <ocra-recipes/TrajectoryThread.h>
#include <ocra-recipes/ControllerClient.h>

class ExampleClient : public ocra_recipes::ControllerClient
{

public:
    ExampleClient (std::shared_ptr<ocra::Model> modelPtr, const int loopPeriod);
    virtual ~ExampleClient ();

protected:
    virtual bool initialize();
    virtual void release();
    virtual void loop();

private:

    double startTime;
    bool trigger;

    Eigen::MatrixXd waypoints;

    std::shared_ptr<ocra_recipes::TrajectoryThread> endEffectorThread;
};

#endif // EXAMPLE_CLIENT_H
