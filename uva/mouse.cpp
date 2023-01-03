
#include"mouse.h"



//LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_RBUTTONDOWN:
//		originalPos.x = LOWORD(lParam);
//		originalPos.y = HIWORD(lParam);
//		ClientToScreen(hwnd, &originalPos);
//		SetCapture(hwnd);
//		ShowCursor(false);
//		bRotateView = true;
//		break;
//	case WM_RBUTTONUP:
//		SetCursorPos(originalPos.x, originalPos.y);
//		ReleaseCapture();
//		ShowCursor(true);
//		bRotateView = false;
//		break;
//	case WM_MOUSEMOVE:
//		if (bRotateView)
//		{
//			POINT currentPos;
//			currentPos.x = LOWORD(lParam);
//			currentPos.y = HIWORD(lParam);
//			ClientToScreen(hwnd, &currentPos);
//			int deltaX = currentPos.x - originalPos.x;
//			int deltaY = currentPos.y - originalPos.y;
//			float angleRotatedByRight = (float)deltaY / 1000.0f;
//			float angleRotatedByUp = (float)deltaX / 1000.0f;
//			camera.Yaw(-angleRotatedByUp);
//			camera.Pitch(-angleRotatedByRight);
//			SetCursorPos(originalPos.x, originalPos.y);
//		}
//		break;
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case 'A':
//			camera.mbMoveLeft = true;
//			break;
//		case'D':
//			camera.mbMoveRight = true;
//			break;
//		case'W':
//			camera.mbMoveForward = true;
//			break;
//		case'S':
//			camera.mbMoveBack = true;
//			break;
//		}
//		break;
//	case WM_KEYUP:
//		switch (wParam)
//		{
//		case 'A':
//			camera.mbMoveLeft = false;
//			break;
//		case'D':
//			camera.mbMoveRight = false;
//			break;
//		case'W':
//			camera.mbMoveForward = false;
//			break;
//		case'S':
//			camera.mbMoveBack = false;
//			break;
//		}
//		break;
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		return 0;
//	}
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}
