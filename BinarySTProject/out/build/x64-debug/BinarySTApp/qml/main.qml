import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    id: mainWindow
    visible: true
    width: 1200
    height: 800
    title: "Reactive Binary Trees"
    color: "#1a1a2e"
    
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: welcomePage
        
        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 300
            }
            PropertyAnimation {
                property: "x"
                from: mainWindow.width
                to: 0
                duration: 300
                easing.type: Easing.OutCubic
            }
        }
        
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 300
            }
        }
        
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 300
            }
        }
        
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 300
            }
            PropertyAnimation {
                property: "x"
                from: 0
                to: mainWindow.width
                duration: 300
                easing.type: Easing.InCubic
            }
        }
    }
    
    Component {
        id: welcomePage
        WelcomePage {
            onTreeSelected: function(treeType) {
                stackView.push(operationsPage, {"selectedTreeType": treeType})
            }
        }
    }
    
    Component {
        id: operationsPage
        TreeOperationsPage {
            onBackClicked: {
                stackView.pop()
            }
        }
    }
}