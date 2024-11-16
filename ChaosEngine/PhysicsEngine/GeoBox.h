#pragma once

#include "Common_PhysicsEngine.h"

namespace ChaosEngine
{
    namespace PhysicsEngine
    {
        class GeoBox
        {
        private:
            PhysicalSpace* space;
        public:
            float z_order;
            std::vector<POINT> vec_vertex;
        public:
            GeoBox();
            GeoBox(PhysicalSpace* new_space);

            inline bool SetPhysicalSpace(PhysicalSpace* new_space);
            inline void AddNextVertex(POINT& new_vertex);
            void Update();
            bool IsCollided(GeoBox& other_box);
        };
    }
}