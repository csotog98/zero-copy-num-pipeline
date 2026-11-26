#include "num_types.hpp"
#include <random>
#include <algorithm>
#include <iostream>

//simulated plant (1D hardware)
class SimulatedOneAxisPlant {
    public:
        explicit SimulatedOneAxisPlant(int32_t seed) 
            : rng_(seed), noise_dist_(-max_noise_dist_, max_noise_dist_) {}

        void step(double force, const double dt) {
            force = std::clamp(force, -max_force_, max_force_);
            const double acceleration = (force - damping * velocity_) / mass;
            velocity_ += acceleration * dt;
            velocity_ = std::clamp(velocity_, -max_vel_, max_vel_);
            position_ += velocity_ * dt;
            position_ = std::clamp(position_, -max_pos_, max_pos_);
        }

        double get_position() const {
            return position_;
        }
        //maybe add noise_dist_

    private:
        const double damping = 0.1;
        const double mass = 1.0;
        const double max_noise_dist_ = 0.001;
        const double max_force_ = 10.0;
        const double max_vel_ = 10.0;
        const double max_pos_ = 10.0;
        std::mt19937 rng_;
        std::uniform_real_distribution<double> noise_dist_;
        double position_ = 0.0;
        double velocity_ = 0.0;
};

// controller for simulated plant
class SimulatedOneAxisController {
    public:
        explicit SimulatedOneAxisController(double kp) : kp_(kp) {}

    double compute_force(double desired__pos, double measured_pos, bool& saturated) {
        double dif_pos = desired__pos - measured_pos;
        double raw_force = kp_ * dif_pos;
        double clamped_force = std::clamp(raw_force, -max_force_, max_force_);

        saturated = (raw_force != clamped_force);
        last_force_ = clamped_force;
        return clamped_force;

    }

    double get_last_force() const {return last_force_;}

    private:
        double kp_;
        const double max_force_ = 10.0; //written twice. Once here (controller) and once in plant
        double last_force_ = 0.0;
};


int main(){


    SimulatedOneAxisController control(0.005);
    bool sat = false;

    SimulatedOneAxisPlant plant(-1);
    
    

    double measured_pos = 0;

    for (size_t i = 0; i < 1000; ++i){
        // std::cout << "Hi1!!!" << std::endl;
        double force = control.compute_force(5, measured_pos, sat);
        // std::cout << "Hi2!!!" << std::endl;
        plant.step(force, 0.1);
        measured_pos = plant.get_position();
        std::cout << plant.get_position() << std::endl;
    }

    return 0;
}


