#pragma once
#include "ChaosEngine.h"

/* Type Predefines */

namespace ChaosEngine {

	namespace Model {
		class PropertyModel;
		class CompModel;
	}

	namespace Type {
		struct VirtKeyState;
		class VirtKeyStateBuffer;
		class Texture;
		class TextFormat;
		class Camera;
	}

	namespace CompList {
		class Timer;
		template <typename T_FLOAT>
		class EaseFunc;
		template <typename T_FLOAT>
		class Animation;
	}

	namespace ObjectList {
		class Image;
		class Text;
	}

}


/* Header Includes */

// model
#include "model/PropertyModel.h"
#include "model/CompModel.h"
#include "model/ObjectModel.h"
#include "model/SceneModel.h"


// type
#include "type/VirtKeyStateBuffer.h"
#include "type/Texture.h"
#include "type/TextFormat.h"
#include "type/Camera.h"


// component
#include "component/EaseFunc.h"
#include "component/Animation.h"


// object
#include "object/Image.h"
#include "object/Text.h"


// manager
#include "manager/TextureManager.h"
