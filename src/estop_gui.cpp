#include "estop_gui.h"
#include <pluginlib/class_list_macros.h>

namespace rqt_estop {

estop_gui::estop_gui()
    : rqt_gui_cpp::Plugin(), widget_(0)
{
   setObjectName("EStopGUI");
}

void estop_gui::initPlugin(qt_gui_cpp::PluginContext& context)
{
    // create QWidget
    widget_ = new QWidget();

    // access standalone command line arguments
    QStringList argv = context.argv();

    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);



    //Publisher
    estop_pub_ = getNodeHandle().advertise<std_msgs::Bool>("/e_stop", 10);

    // Set EStop to active (checked)
    ui_.estop_button->setCheckable(true);
    ui_.estop_button->setChecked(true);
    estopActive();

    // CONNECTIONS
    connect(ui_.estop_button, SIGNAL( toggled(bool) ), this, SLOT( on_estop_button_toggled(bool) ) );
}

void estop_gui::shutdownPlugin()
{
}

void estop_gui::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void estop_gui::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}

void estop_gui::estopActive()
{
    ui_.estop_button->setStyleSheet("background-color: rgb(0,255,0); color: black;");
    ui_.estop_button->setText("GO");
    ui_.status_text->setText("EStop active!");
    output_.data = true;
    estop_pub_.publish(output_);
}

void estop_gui::estopInactive()
{
    ui_.estop_button->setStyleSheet("background-color: red; color: white; font: 20pt \"Ubuntu\";");
    ui_.estop_button->setText("STOP");
    ui_.status_text->setText("Robots running...");
    output_.data = false;
    estop_pub_.publish(output_);
}

void rqt_estop::estop_gui::on_estop_button_toggled(bool checked)
{
    if (checked)
        estopActive();
    else
        estopInactive();
}


}  // namespace
PLUGINLIB_EXPORT_CLASS(rqt_estop::estop_gui, rqt_gui_cpp::Plugin)
