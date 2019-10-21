#include "frequency_graph.hpp"

namespace wiet_star
{

frequency_graph::frequency_graph()
{
    x_axis.setTitleText("Częstotliwości");
    x_axis.setRange(20000, 40000);

    y_axis.setTitleText("Amplituda");
    y_axis.setMin(-1);

    main_graph.addSeries(&main_series);
    main_graph.legend()->hide();
    main_graph.setAxisX(&x_axis, &main_series);
    main_graph.setAxisY(&y_axis, &main_series);
    main_graph.setTitle("Wynik transformaty Fouriera");

    setChart(&main_graph);
}

} // wiet_star
