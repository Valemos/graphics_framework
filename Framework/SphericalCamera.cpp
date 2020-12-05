#include "SphericalCamera.h"

#include <cmath>
#include <iostream>


SphericalCamera::SphericalCamera(Vector3 camera_target, Vector3 camera_up, float radius, float phi_deg,
                                 float theta_deg, float camera_speed) :
        camera_up_(camera_up),
        radius_(radius),
        phi_angle_(phi_deg / 180 * pi),
        theta_angle_(theta_deg / 180 * pi),
        move_speed_(camera_speed)
{
    UpdatePosition();
}

void SphericalCamera::DecrementRadius() {
    radius_ -= move_speed_;
    UpdatePosition();
}

void SphericalCamera::IncrementRadius() {
    radius_ += move_speed_;
    UpdatePosition();
}

void SphericalCamera::UpdatePosition() {
    camera_position_.x = radius_ * sin(theta_angle_) * cos(phi_angle_);
    camera_position_.z = radius_ * sin(theta_angle_) * sin(phi_angle_);
    camera_position_.y = radius_ * cos(theta_angle_);
    camera_position_ += camera_target_;
}


void SphericalCamera::UpdateTarget(Vector3& new_target) {
    camera_target_ = new_target;
    UpdatePosition();
}

float SphericalCamera::get_radius() const {
    return radius_;
}

void SphericalCamera::IncrementPhi(float amount) {
    phi_angle_ += amount;

    if (abs(phi_angle_) - pi2 > VECTOR_FLOAT_ACCURACY)
    {
        phi_angle_ += phi_angle_ < 0 ? pi2 : -pi2;
    }
}

void SphericalCamera::IncrementTheta(float amount) {

    float prev_theta_angle = theta_angle_;
    theta_angle_ += amount;

    // modify theta_angle to be [0, 2*PI]
    if (theta_angle_ < 0)
    {
        theta_angle_ += pi2;
    }
    else if (theta_angle_ - pi2 > VECTOR_FLOAT_ACCURACY)
    {
        theta_angle_ -= pi2;
    }

    // make next angle the biggest no matter if angle decreases or increases
    float next_theta_angle = theta_angle_;
    if (prev_theta_angle > theta_angle_)
    {
        next_theta_angle = prev_theta_angle;
        prev_theta_angle = theta_angle_;
    }


    // must change up vector when theta passes 0 degrees and 180 degrees
    // to maintain the same orientation relative to center of a scene
    if (prev_theta_angle < bot_angle_ && bot_angle_ < next_theta_angle ||
        prev_theta_angle < top_angle_ && top_angle_ < next_theta_angle)
    {
        camera_up_ = camera_up_ * -1;
    }
}

bool SphericalCamera::MoveCamera(const Vector3& direction) {

    bool update_coordinate = false;

    if (abs(direction.x) > VECTOR_FLOAT_ACCURACY)
    {
        IncrementPhi(direction.x * move_speed_);
        update_coordinate = true;
    }

    if (abs(direction.y) > VECTOR_FLOAT_ACCURACY)
    {
        IncrementTheta(direction.y * move_speed_);
        update_coordinate = true;
    }

    if (update_coordinate){
        UpdatePosition();
    }

    return update_coordinate;
}

void SphericalCamera::UpdateCamera(Camera &camera) {
    camera.UpdateCameraPosition(camera_position_);
    camera.UpdateCameraTarget(camera_target_);
    camera.UpdateCameraUp(camera_up_);
    std::cout <<
        "t: " << theta_angle_ * 180 / pi <<
        " p: " << phi_angle_ * 180 / pi <<
        " up: " << camera.get_up().Str() <<
    std::endl;
}
