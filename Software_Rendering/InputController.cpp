#include "InputController.h"

bool InputController::GetKeyDown(int keyCode)
{
    return GetKeyState(keyCode) & 0x8000;
}