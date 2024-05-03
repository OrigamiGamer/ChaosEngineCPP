#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    // Types which engine predefined
    namespace Type {

        // Callback EngineProc
        typedef BOOL(CALLBACK* ENGINEPROC)();

        // Initial Property
        struct WindowInitialProperty;
        struct EngineStartupProperty;

        struct WindowInitialProperty {
            int width = CW_USEDEFAULT, height = CW_USEDEFAULT;
            int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
            std::wstring WndTitle = L"New Game";
            HWND hWndParent = NULL;
        };
        struct EngineStartupProperty {
            ENGINEPROC pGameMain = nullptr;
            ENGINEPROC pGameExit = nullptr;
            int FPS = 60;
        };


        // Basic Types
        struct SCALE;
        struct SIZE;
        struct SIZE_3D;
        struct POS;
        struct POS_3D;
        struct COLOR;
        struct VECTOR;
        struct FORCE;

        struct SCALE {
            float x, y, global;

            SCALE() = default;
            SCALE(float x, float y, float global) : x(x), y(y), global(global) {};

            bool operator==(SCALE other) const {
                return x == other.x || y == other.y;
            }
            bool operator!=(SCALE other) const {
                return !(*this == other);
            }
        };

        struct SIZE {
            float width, height;

            SIZE() = default;
            SIZE(float width, float height) : width(width), height(height) {};

            bool operator==(SIZE& other) const {
                return width == other.width || height == other.height;
            }
            bool operator!=(SIZE& other) const {
                return !(*this == other);
            }
            SIZE operator+(SIZE& other) {
                return SIZE(width + other.width, height + other.height);
            }
            SIZE operator-(SIZE& other) {
                return SIZE(width - other.width, height - other.height);
            }
            SIZE operator+=(SIZE& other) {
                return *this + other;
            }
            SIZE operator-=(SIZE& other) {
                return *this - other;
            }
            SIZE SIZE::operator*(SCALE& scale) {
                return SIZE(width * scale.x * scale.global, height * scale.y * scale.global);
            }
        };
        struct SIZE_3D {
            float width, height, length;

            SIZE_3D() = default;
            SIZE_3D(float width, float height, float length) : width(width), height(height), length(length) {};

            bool operator==(SIZE_3D& other) const {
                return width == other.width && height == other.height && length == other.length;
            }
            bool operator!=(SIZE_3D& other) const {
                return !(*this == other);
            }
            SIZE_3D operator+(SIZE_3D& other) {
                return SIZE_3D(width + other.width, height + other.height, length + other.length);
            }
            SIZE_3D operator-(SIZE_3D& other) {
                return SIZE_3D(width - other.width, height - other.height, length + other.length);
            }
            SIZE_3D operator+=(SIZE_3D& other) {
                return *this + other;
            }
            SIZE_3D operator-=(SIZE_3D& other) {
                return *this - other;
            }
        };

        struct POS {
            float x = 0, y = 0;

            POS() = default;
            POS(float x, float y) : x(x), y(y) {};

            bool operator==(POS other) const {
                return x == other.x && y == other.y;
            }
            bool operator!=(POS other) const {
                return !(*this == other);
            }
            POS operator+(POS other) {
                return POS(x + other.x, y + other.y);
            }
            POS operator-(POS other) {
                return POS(x - other.x, y - other.y);
            }
            POS operator+=(POS other) {
                return *this + other;
            }
            POS operator-=(POS other) {
                return *this - other;
            }
            POS operator*(SCALE& scale) {
                return POS(x * scale.x * scale.global, y * scale.y * scale.global);
            }
        };
        struct POS_3D {
            float x, y, z;

            POS_3D() = default;
            POS_3D(float x, float y, float z) : x(x), y(y), z(z) {};

            bool operator==(POS_3D other) const {
                return x == other.x && y == other.y && z == other.z;
            }
            bool operator!=(POS_3D other) const {
                return !(*this == other);
            }
            POS_3D operator+(POS_3D other) {
                return POS_3D(x + other.x, y + other.y, z + other.z);
            }
            POS_3D operator-(POS_3D other) {
                return POS_3D(x - other.x, y - other.y, z + other.z);
            }
            POS_3D operator+=(POS_3D other) {
                return *this + other;
            }
            POS_3D operator-=(POS_3D other) {
                return *this - other;
            }
        };

        struct COLOR {
            UINT32 rgb;
            FLOAT alpha;

            COLOR() = default;
            COLOR(UINT32 rgb, FLOAT alpha) : rgb(rgb), alpha(alpha) {};
            //COLOR(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) : alpha(alpha) {}; // NEED: ARGB Color Mixer
        };

        struct VECTOR {
            double magnitude = 0;
            double direction = 0;

            VECTOR() = default;
            VECTOR(double magnitude, double direction) :magnitude(magnitude), direction(direction) {};
        };

        enum FORCE_TYPE{
            FORCE_TYPE_APPLIED = 0,
            FORCE_TYPE_GRAVITY = 1,
            FORCE_TYPE_NORMAL = 2,
            FORCE_TYPE_FRICTION = 3,
            FORCE_TYPE_TENSION = 4,
            FORCE_TYPE_MAGNETISM = 5,
        };

        struct FORCE : public VECTOR {
            UINT type;

            FORCE() = default;
            FORCE(double magnitude, double direction, UINT type = FORCE_TYPE_APPLIED) {
                this->magnitude = magnitude;
                this->direction = direction;
                this->type = type;
            };
        };


     

        // Class Predefined
        struct VirtKeyState;
        class VirtKeyStateBuffer;
        class Texture;
        class TextFormat;
        class Camera;

        class Timer;
        template <typename T_FLOAT>
        class EaseFunc;
        template <typename T_FLOAT>
        class Animation;

    }

}
