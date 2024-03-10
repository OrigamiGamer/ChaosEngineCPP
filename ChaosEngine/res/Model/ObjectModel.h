#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Type {

        struct STD_VEC_FORCE_LIST {
            std::vector<Type::FORCE>
                gravity,    // 引力
                friction,   // 摩擦力
                normal,     // 支持力
                tension,    // 张力
                magnetism,  // 磁力
                applied;    // 作用力
        };

    }

    namespace Model {

        class ObjectModel : public CompModel {
        public:
            Type::Camera* pCamera = nullptr;

            Type::SIZE size = { 0, 0 };
            Type::POS anchorPos = { 0, 0 }; // anchor position related to the size.
            Type::SCALE scale = { 1, 1, 1 };
            Type::POS pos = { 0, 0 };
            double rotation = 0;

            bool use_physics = false;   // Do NOT use physics to this Object by default.
            bool fixed = false; // Do NOT fix this object by default.
            double mass = 0;    // kg
            double elastic_k = 1;   // elastic coefficient
            double force_x = 0;  // N
            double force_y = 0;  // N
            double velocity_x = 0;  // m/s
            double velocity_y = 0;  // m/s

            Type::STD_VEC_FORCE_LIST vec_force;

        public:
            ObjectModel();

            void SetAnchorPosInSite();
            inline Type::POS GetAbsAnchorPos();
            inline Type::POS GetOriginPos();
            inline Type::SIZE GetOriginSize();
            inline Type::POS GetRenderPos();
            inline Type::SIZE GetRenderSize();

            void ApplyForce(const Type::FORCE& new_force);
            void ClearForce();
            inline void ComposeForce(const Type::FORCE& new_force);
            inline bool IsCollided(const Type::POS& obj_pos, const Type::SIZE& obj_size) const;
            inline bool IsCollided(Model::ObjectModel& obj) const;
            inline bool IsCollided(Model::ObjectModel*& obj) const;

        };

    }

}