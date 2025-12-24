import QtQuick
import QtQuick.Controls

Rectangle {
    id: welcomePage
    anchors.fill: parent

    signal treeSelected(string treeType)

    // Dark shining background
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#030303" }
        GradientStop { position: 1.0; color: "#000000" }
    }

    // Simple animated background dots
    Repeater {
        model: 20
        Rectangle {
            width: 6; height: 6; radius: 3
            color: "#FFCC00"
            opacity: 0.12 + Math.random() * 0.2
            x: Math.random() * parent.width
            y: Math.random() * parent.height

            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { from: -10; to: parent.height + 10; duration: 4000 + Math.random() * 3000 }
                ScriptAction { script: parent.y = -10 }
            }

            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.05; to: 0.3; duration: 1500 + Math.random() * 2000 }
                NumberAnimation { from: 0.3; to: 0.05; duration: 1500 + Math.random() * 2000 }
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 50

        // Title with glow effect
        Text {
            text: "Reactive Binary Trees"
            font.pixelSize: 56
            font.bold: true
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter

            layer.enabled: true
            // glow effect removed for compatibility; keep layer enabled for smoother rendering

            SequentialAnimation on scale {
                running: true
                loops: Animation.Infinite
                NumberAnimation { from: 1.0; to: 1.05; duration: 1500; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 1.05; to: 1.0; duration: 1500; easing.type: Easing.InOutQuad }
            }
        }

        Text {
            text: "Select Your Tree Structure"
            font.pixelSize: 24
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter

            SequentialAnimation on opacity {
                running: true
                loops: Animation.Infinite
                NumberAnimation { from: 0.5; to: 1.0; duration: 2000; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 1.0; to: 0.5; duration: 2000; easing.type: Easing.InOutQuad }
            }
        }

        Row {
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter

          
          // BST Button - Red
TreeButton {
    buttonText: "Binary Search\nTree (BST)"
    gradientColor1: "#EF4444"
    gradientColor2: "#B91C1C"
    glowColor: "#EF4444"
    textColor: "#ffffff"
    onClicked: treeSelected("BST")
}

// AVL Button - Yellow
TreeButton {
    buttonText: "AVL\nTree"
    gradientColor1: "#FFCC00"
    gradientColor2: "#FFD54F"
    glowColor: "#FFCC00"
    textColor: "#000000"
    onClicked: treeSelected("AVL")
}

// Red-Black Button - Navy
TreeButton {
    buttonText: "Red-Black\nTree"
    gradientColor1: "#003366"
    gradientColor2: "#002244"
    glowColor: "#003366"
    textColor: "#ffffff"
    onClicked: treeSelected("RB")
}

// Tree Button Component - SCALE ONLY
component TreeButton: Rectangle {
    id: button
    width: 250
    height: 150
    radius: 16

    property string buttonText: ""
    property string gradientColor1: "#667eea"
    property string gradientColor2: "#764ba2"
    property string glowColor: "#667eea"
    property color textColor: "#ffffff"
    signal clicked()

    // Static gradient - NO color switching
    gradient: Gradient {
        GradientStop { position: 0.0; color: button.gradientColor1 }
        GradientStop { position: 1.0; color: button.gradientColor2 }
    }

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 12
        color: mouseArea.containsMouse ? button.glowColor : button.gradientColor1
        spread: mouseArea.containsMouse ? 0.4 : 0.25
        radius: mouseArea.containsMouse ? 16 : 8
    }

    // ONLY scale on hover
    scale: mouseArea.containsMouse ? 1.06 : 1.0

    Behavior on scale { 
        NumberAnimation { 
            duration: 220
            easing.type: Easing.OutBack 
        } 
    }

    Text {
        text: button.buttonText
        anchors.centerIn: parent
        font.pixelSize: 20
        font.bold: true
        color: button.textColor  // Static text color - NO switching
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            clickAnimation.start()
            button.clicked()
        }
    }

    SequentialAnimation {
        id: clickAnimation
        NumberAnimation { 
            target: button
            property: "scale"
            to: 0.96
            duration: 90 
        }
        NumberAnimation { 
            target: button
            property: "scale"
            to: mouseArea.containsMouse ? 1.06 : 1.0
            duration: 120 
        }
    }
}

component DropShadow: ShaderEffect {
    property variant source
    property color color: "black"
    property real spread: 0.0
    property int samples: 0
    property real radius: 0
}

}

    } // close Column

} // close Rectangle