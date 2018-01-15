#ifndef IMGUI_H
# define IMGUI_H
# include "graphics.h"

typedef struct	s_ui_state
{
	int	mousex;
	int	mousey;
	int	mousedown;
	int	hotitem;
	int	activeitem;
}		t_ui_state;

t_ui_state	*make_ui(void);
int	regionhit(t_ui_state *ui, t_rect_int rect);
int	button(t_window *win, t_ui_state *ui, int id, t_rect_int rect, char *str);
void	update_ui_coord(t_ui_state *ui, int x, int y);
void	update_ui_mouse_button(t_ui_state *ui, int button);
int	slider(t_window *win, t_ui_state *ui, int id, t_rect_int rect, int max, int *value);
t_rect_int	make_rect(int x, int y, int w, int h);

#endif
