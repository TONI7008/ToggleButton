#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QColorDialog>
#include "togglebutton.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Main window
    QWidget window;
    window.setWindowTitle("ToggleButton Test Application");
    window.resize(600, 700);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    
    // === Basic Toggle Buttons Section ===
    QGroupBox *basicGroup = new QGroupBox("Basic Toggle Buttons");
    QVBoxLayout *basicLayout = new QVBoxLayout(basicGroup);
    
    // Default toggle button
    QHBoxLayout *defaultLayout = new QHBoxLayout();
    QLabel *defaultLabel = new QLabel("Default:");
    ToggleButton *defaultToggle = new ToggleButton();
    defaultLayout->addWidget(defaultLabel);
    defaultLayout->addWidget(defaultToggle);
    defaultLayout->addStretch();
    basicLayout->addLayout(defaultLayout);
    
    // Pre-toggled button
    QHBoxLayout *toggledLayout = new QHBoxLayout();
    QLabel *toggledLabel = new QLabel("Initially On:");
    ToggleButton *toggledButton = new ToggleButton();
    toggledButton->setToggled(true);
    toggledLayout->addWidget(toggledLabel);
    toggledLayout->addWidget(toggledButton);
    toggledLayout->addStretch();
    basicLayout->addLayout(toggledLayout);
    
    // Disabled button
    QHBoxLayout *disabledLayout = new QHBoxLayout();
    QLabel *disabledLabel = new QLabel("Disabled:");
    ToggleButton *disabledButton = new ToggleButton();
    disabledButton->setEnabled(false);
    disabledLayout->addWidget(disabledLabel);
    disabledLayout->addWidget(disabledButton);
    disabledLayout->addStretch();
    basicLayout->addLayout(disabledLayout);
    
    mainLayout->addWidget(basicGroup);
    
    // === Customized Styles Section ===
    QGroupBox *stylesGroup = new QGroupBox("Custom Styles");
    QVBoxLayout *stylesLayout = new QVBoxLayout(stylesGroup);
    
    // Blue theme
    QHBoxLayout *blueLayout = new QHBoxLayout();
    QLabel *blueLabel = new QLabel("Blue Theme:");
    ToggleButton *blueToggle = new ToggleButton();
    blueToggle->setActiveColor(QColor("#2196F3"));
    blueToggle->setInactiveColor(QColor("#BBDEFB"));
    blueToggle->setThumbColor(Qt::white);
    blueLayout->addWidget(blueLabel);
    blueLayout->addWidget(blueToggle);
    blueLayout->addStretch();
    stylesLayout->addLayout(blueLayout);
    
    // Green theme
    QHBoxLayout *greenLayout = new QHBoxLayout();
    QLabel *greenLabel = new QLabel("Green Theme:");
    ToggleButton *greenToggle = new ToggleButton();
    greenToggle->setActiveColor(QColor("#4CAF50"));
    greenToggle->setInactiveColor(QColor("#C8E6C9"));
    greenToggle->setThumbColor(Qt::white);
    greenLayout->addWidget(greenLabel);
    greenLayout->addWidget(greenToggle);
    greenLayout->addStretch();
    stylesLayout->addLayout(greenLayout);
    
    // Dark theme
    QHBoxLayout *darkLayout = new QHBoxLayout();
    QLabel *darkLabel = new QLabel("Dark Theme:");
    ToggleButton *darkToggle = new ToggleButton();
    darkToggle->setActiveColor(QColor("#424242"));
    darkToggle->setInactiveColor(QColor("#757575"));
    darkToggle->setThumbColor(QColor("#FFC107"));
    darkLayout->addWidget(darkLabel);
    darkLayout->addWidget(darkToggle);
    darkLayout->addStretch();
    stylesLayout->addLayout(darkLayout);
    
    // With border
    QHBoxLayout *borderLayout = new QHBoxLayout();
    QLabel *borderLabel = new QLabel("With Border:");
    ToggleButton *borderToggle = new ToggleButton();
    borderToggle->setBorderEnabled(true);
    borderToggle->setActiveColor(QColor("#FF5722"));
    borderToggle->setInactiveColor(Qt::white);
    borderToggle->setThumbColor(QColor("#FF5722"));
    borderLayout->addWidget(borderLabel);
    borderLayout->addWidget(borderToggle);
    borderLayout->addStretch();
    stylesLayout->addLayout(borderLayout);
    
    mainLayout->addWidget(stylesGroup);
    
    // === Interactive Controls Section ===
    QGroupBox *controlsGroup = new QGroupBox("Interactive Controls");
    QVBoxLayout *controlsLayout = new QVBoxLayout(controlsGroup);
    
    // Test toggle button for controls
    ToggleButton *testToggle = new ToggleButton();
    testToggle->setMinimumSize(80, 40);
    QHBoxLayout *testToggleLayout = new QHBoxLayout();
    testToggleLayout->addWidget(new QLabel("Test Button:"));
    testToggleLayout->addWidget(testToggle);
    testToggleLayout->addStretch();
    controlsLayout->addLayout(testToggleLayout);
    
    // Animation duration control
    QHBoxLayout *durationLayout = new QHBoxLayout();
    durationLayout->addWidget(new QLabel("Animation Duration (ms):"));
    QSpinBox *durationSpin = new QSpinBox();
    durationSpin->setRange(50, 1000);
    durationSpin->setValue(200);
    durationSpin->setSingleStep(50);
    durationLayout->addWidget(durationSpin);
    durationLayout->addStretch();
    controlsLayout->addLayout(durationLayout);
    
    QObject::connect(durationSpin, QOverload<int>::of(&QSpinBox::valueChanged),
                     testToggle, &ToggleButton::setAnimationDuration);
    
    // Easing curve control
    QHBoxLayout *easingLayout = new QHBoxLayout();
    easingLayout->addWidget(new QLabel("Easing Curve:"));
    QComboBox *easingCombo = new QComboBox();
    easingCombo->addItem("InOutQuad", QEasingCurve::InOutQuad);
    easingCombo->addItem("OutBounce", QEasingCurve::OutBounce);
    easingCombo->addItem("OutElastic", QEasingCurve::OutElastic);
    easingCombo->addItem("InOutCubic", QEasingCurve::InOutCubic);
    easingCombo->addItem("Linear", QEasingCurve::Linear);
    easingLayout->addWidget(easingCombo);
    easingLayout->addStretch();
    controlsLayout->addLayout(easingLayout);
    
    QObject::connect(easingCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [testToggle, easingCombo](int index) {
        testToggle->setEasing(static_cast<QEasingCurve::Type>(
            easingCombo->itemData(index).toInt()));
    });
    
    // Color pickers
    QHBoxLayout *colorLayout = new QHBoxLayout();
    
    QPushButton *activeColorBtn = new QPushButton("Active Color");
    QObject::connect(activeColorBtn, &QPushButton::clicked, [testToggle]() {
        QColor color = QColorDialog::getColor(testToggle->activeColor(), 
                                              nullptr, "Choose Active Color");
        if (color.isValid()) {
            testToggle->setActiveColor(color);
        }
    });
    
    QPushButton *inactiveColorBtn = new QPushButton("Inactive Color");
    QObject::connect(inactiveColorBtn, &QPushButton::clicked, [testToggle]() {
        QColor color = QColorDialog::getColor(testToggle->inactiveColor(), 
                                              nullptr, "Choose Inactive Color");
        if (color.isValid()) {
            testToggle->setInactiveColor(color);
        }
    });
    
    QPushButton *thumbColorBtn = new QPushButton("Thumb Color");
    QObject::connect(thumbColorBtn, &QPushButton::clicked, [testToggle]() {
        QColor color = QColorDialog::getColor(testToggle->thumbColor(), 
                                              nullptr, "Choose Thumb Color");
        if (color.isValid()) {
            testToggle->setThumbColor(color);
        }
    });
    
    colorLayout->addWidget(activeColorBtn);
    colorLayout->addWidget(inactiveColorBtn);
    colorLayout->addWidget(thumbColorBtn);
    controlsLayout->addLayout(colorLayout);
    
    // Border control
    QHBoxLayout *borderControlLayout = new QHBoxLayout();
    QPushButton *toggleBorderBtn = new QPushButton("Toggle Border");
    QObject::connect(toggleBorderBtn, &QPushButton::clicked, [testToggle]() {
        testToggle->setBorderEnabled(!testToggle->borderEnabled());
    });
    borderControlLayout->addWidget(toggleBorderBtn);
    borderControlLayout->addStretch();
    controlsLayout->addLayout(borderControlLayout);
    
    mainLayout->addWidget(controlsGroup);
    
    // === State Display Section ===
    QGroupBox *stateGroup = new QGroupBox("State Display");
    QVBoxLayout *stateLayout = new QVBoxLayout(stateGroup);
    
    QLabel *stateLabel = new QLabel("Toggle states will appear here:");
    stateLayout->addWidget(stateLabel);
    
    // Connect all toggles to update state label
    auto updateState = [stateLabel](ToggleButton* toggle, const QString& name) {
        QObject::connect(toggle, &ToggleButton::toggled, [stateLabel, name](bool state) {
            stateLabel->setText(QString("%1: %2").arg(name).arg(state ? "ON" : "OFF"));
        });
    };
    
    updateState(defaultToggle, "Default");
    updateState(toggledButton, "Initially On");
    updateState(blueToggle, "Blue Theme");
    updateState(greenToggle, "Green Theme");
    updateState(darkToggle, "Dark Theme");
    updateState(borderToggle, "With Border");
    updateState(testToggle, "Test Button");
    
    mainLayout->addWidget(stateGroup);
    
    // Add stretch at the bottom
    mainLayout->addStretch();
    
    window.show();
    
    return app.exec();
}