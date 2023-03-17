#include "selector.h"
#include "canvas.h"


Error select_action(Actions action, Event event){

    static Figure figure = figure_init();

    Error rc = OK;

    switch (action)
    {
        case DRAW:
            rc = draw_figure(figure, event.canvas);
            break;
        case LOAD:
            rc = load_figure(figure, event.file_name);
            break;
        case SCALE:
            rc = scale_figure(figure, figure.center, event.change);
            break;
        case SPIN:
            rc = spin_figure(figure, figure.center, event.change);
            break;
        case MOVE:
            rc = move_figure(figure, figure.center, event.change);
            break;
        case QUIT:
            figure_free(figure);
            break;
        default:
            rc = ERR_EXTRA_ERROR;
    }

    return rc;
}
