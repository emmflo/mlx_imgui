#include "graphics.h"
#include "imgui.h"
#include <stdlib.h>

t_rect_int	make_rect(int x, int y, int w, int h)
{
	t_rect_int	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

t_ui_state	*make_ui(void)
{
	t_ui_state *ui;

	if(!(ui = (t_ui_state*)malloc(sizeof(t_ui_state))))
		return (NULL);
	ui->mousex = 0;
	ui->mousey = 0;
	ui->mousedown = 0;
	ui->hotitem = 0;
	ui->activeitem = 0;
	return (ui);
}

void	update_ui_coord(t_ui_state *ui, int x, int y)
{
	ui->mousex = x;
	ui->mousey = y;
}

void	update_ui_mouse_button(t_ui_state *ui, int button)
{
	ui->mousedown = button;
}

int	button(t_window *win, t_ui_state *ui, int id, t_rect_int rect, char *str)
{
	t_rect_int	shadow;

	//printf("%d %d\n", ui->hotitem, ui->activeitem);
	if (regionhit(ui, rect))
	{
		ui->hotitem = id;
		if (ui->activeitem == 0 && ui->mousedown)
			ui->activeitem = id;
	}
	else if(ui->hotitem == id)
	{
		ui->hotitem = 0;
		ui->activeitem = 0;
	}
	shadow.x = rect.x + 8;
	shadow.y = rect.y + 8;
	shadow.w = rect.w;
	shadow.h = rect.h;
	g_rect_fill(win->img_front, shadow, 0xCCCCCC);
	if (ui->hotitem == id)
	{
		g_rect_fill(win->img_front, rect, 0xFFFFFF);
	}
	else
	{
		g_rect_fill(win->img_front, rect, 0xAAAAAA);
	}
	//mlx_string_put(win->mlx_ptr, win->win_ptr, rect.x, rect.y + rect.h / 2, 0, str);
	g_add_to_text_buffer(win, g_make_text(rect.x + 5, rect.y + rect.h / 2, 0, str));
	if (ui->mousedown == 0 &&
		ui->hotitem == id &&
		ui->activeitem == id)
		return (1);
	return (0);
}

int	slider(t_window *win, t_ui_state *ui, int id, t_rect_int rect, int max, int *value)
{
	int		v;
	int		mousepos;
	t_rect_int	thumb;

	if (regionhit(ui, rect))
	{
		ui->hotitem = id;
		if (ui->activeitem == 0 && ui->mousedown)
			ui->activeitem = id;
	}
	else if (ui->hotitem == id)
		ui->hotitem = 0;
	if (ui->activeitem == id && !ui->mousedown)
		ui->activeitem = 0;
	g_rect_fill(win->img_front, rect, 0x777777);
	if (rect.w < rect.h)
	{
		thumb.x = rect.x + 4;
		thumb.h = rect.h / 16;
		thumb.y = rect.y + 4 + (*value * (rect.h - 8 - thumb.h)) / max;
		thumb.w = rect.w - 8;
	}
	else
	{
		thumb.y = rect.y + 4;
		thumb.w = rect.w / 16;
		thumb.x = rect.x + 4 + (*value * (rect.w - 8 - thumb.w)) / max;
		thumb.h = rect.h - 8;

	}
	if (ui->activeitem == id || ui->hotitem == id)
		g_rect_fill(win->img_front, thumb, 0xFFFFFF);
	else
		g_rect_fill(win->img_front, thumb, 0xAAAAAA);
	if (ui->activeitem == id)
	{
		if (rect.w < rect.h)
		{
			mousepos = ui->mousey - (rect.y + 4);
			if (mousepos < 0)
				mousepos = 0;
			if (mousepos > rect.h - 8)
				mousepos = rect.h - 8;
			v = mousepos * max / (rect.h - 8);
		}
		else
		{
			mousepos = ui->mousex - (rect.x + 4);
			if (mousepos < 0)
				mousepos = 0;
			if (mousepos > rect.w - 8)
				mousepos = rect.w - 8;
			v = mousepos * max / (rect.w - 8);
		}
		if (v != *value)
		{
			printf("V %d\n", v);
			*value = v;
			return (1);
		}
	}
	return (0);
}

int	color_picker(t_window *win, t_ui_state *ui, int id, t_rect_int rect, t_hsv *color, t_hsv *color_select)
{
	int	hue_value;

	if (regionhit(ui, make_rect(rect.x, rect.y, rect.w, rect.h - 32)))
	{
		ui->hotitem = id;
		if (ui->activeitem == 0 && ui->mousedown)
			ui->activeitem = id;
	}
	else if (ui->hotitem == id)
		ui->hotitem = 0;
	if (ui->activeitem == id && !ui->mousedown)
		ui->activeitem = 0;
	g_rect_fill(win->img_front, rect, 0x777777);
	hue_value = (int)(color->hue * 1000 / 360);
	slider(win, ui, 255, make_rect(rect.x, rect.y + rect.h - 32, rect.w, 32), 1000, &hue_value);
	color->hue = hue_value / 1000.0 * 360.0;
	g_rect_hsv_gradient(win->img_front, make_rect(rect.x, rect.y, rect.w, rect.h - 32), color->hue);
	if (ui->hotitem == id)
	{
		color->saturation = (ui->mousex - rect.x) / (double)rect.w;
		color->value = ((rect.h - 32) - (ui->mousey - rect.y)) / (double)(rect.h - 32);
		//color->saturation = 1;
		//color->value = 1;
		if (ui->activeitem == id)
		{
			if (ui->mousedown)
			{
				color_select->hue = color->hue;
				color_select->saturation = color->saturation;
				color_select->value = color->value;
				return (1);
			}
		}
	}
	return (0);
}
