#pragma once
#include "ChaosEngine.h"

/* Type Predefines */

namespace ChaosEngine {
	namespace Type {

		// type
		struct VirtKeyState;
		class VirtKeyStateBuffer;
		class Texture;
		class TextFormat;
		class Camera;

		// model
		class PropertyModel;
		class CompModel;

		// component
		class Timer;
		template <typename T_FLOAT>
		class EaseFunc;
		template <typename T_FLOAT>
		class Animation;

	}
}


/* Header Includes */

// type
#include "type/VirtKeyStateBuffer.h"
#include "type/Texture.h"
#include "type/TextFormat.h"
#include "type/Camera.h"


// model
#include "model/PropertyModel.h"
#include "model/CompModel.h"
#include "model/ObjectModel.h"
#include "model/SceneModel.h"


// component
#include "component/EaseFunc.h"
#include "component/Animation.h"


// object



// manager
