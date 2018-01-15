#include "imgui.h"
#include "graphics.h"

int	regionhit(t_ui_state *ui, t_rect_int rect)
{
	return !(ui->mousex < rect.x ||
		ui->mousey < rect.y ||
		ui->mousex >= rect.x + rect.w ||
		ui->mousey >= rect.y + rect.h);
}
