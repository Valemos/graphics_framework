#ifndef GRAPHICALFRAMEWORK_SPHERICALCAMERA_H
#define GRAPHICALFRAMEWORK_SPHERICALCAMERA_H


#include <Vector3.h>
#include <draw_objects/Camera.h>

static constexpr float pi = 3.141592653589793f;
static constexpr float pi2 = pi * 2;

class SphericalCamera {

    Camera& camera_;

    Vector3 camera_position_;
    Vector3 camera_target_;
    Vector3 camera_up_;
    Vector3 up_{0, 1, 0};

    float move_speed_;
    const float top_angle_ = 0;
    const float bot_angle_ = pi;
    float theta_angle_;
    float phi_angle_;
    float radius_;

public:


    SphericalCamera(Camera &camera,
                    Vector3 camera_target, Vector3 camera_up,
                    float radius = 1.f,
                    float phi_deg = 90.f, float theta_deg = 90.f,
                    float camera_speed = 0.15f);

    void UpdatePosition();

    void DecrementRadius();
    void IncrementRadius();

    // updates position if needed
    bool MoveCamera(const Vector3& direction);

    void IncrementPhi(float amount);
    void IncrementTheta(float amount);

    Camera &get_camera();

    float get_radius() const;

    void UpdateTarget(Vector3 &new_target);
};


#endif //GRAPHICALFRAMEWORK_SPHERICALCAMERA_H
