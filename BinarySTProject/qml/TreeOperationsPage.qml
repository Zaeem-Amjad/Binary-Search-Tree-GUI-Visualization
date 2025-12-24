import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: operationsPage
    anchors.fill: parent

    property string selectedTreeType: "BST"
    signal backClicked()

    ListModel { id: memoryModel }

    Component.onCompleted: {
        treeManager.setTreeType(selectedTreeType)
        // ensure initial fit using Flickable viewport size
        canvas.zoomToFit(flickableCanvas.width, flickableCanvas.height)
    }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#030303" }
        GradientStop { position: 1.0; color: "#000000" }
    }

    Repeater {
        model: 20
        Rectangle {
            width: 6; height: 6; radius: 3
            color: "#FFCC00"
            opacity: 0.12 + Math.random() * 0.2
            x: Math.random() * operationsPage.width
            y: Math.random() * operationsPage.height

            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { from: -10; to: operationsPage.height + 10; duration: 4000 + Math.random() * 3000 }
                ScriptAction { script: parent.y = -10 }
            }

            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.05; to: 0.3; duration: 1500 + Math.random() * 2000 }
                NumberAnimation { from: 0.3; to: 0.05; duration: 1500 + Math.random() * 2000 }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            radius: 8
            color: "#0056b3"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 12

                Text {
                    text: selectedTreeType === "BST" ? "Binary Search Tree" : 
                          selectedTreeType === "AVL" ? "AVL Tree" : "Red-Black Tree"
                    font.family: "Roboto"
                    font.pixelSize: 24
                    font.bold: true
                    color: "#FFFFFF"
                    Layout.fillWidth: true
                }

                Button {
                    text: "← Back"
                    font.family: "Roboto"
                    font.pixelSize: 14
                    font.bold: true

                    background: Rectangle {
                        radius: 8
                        color: "#0056b3"
                        border.color: "#003366"
                        border.width: 1
                    }

                    contentItem: Text {
                        text: parent.text
                        font: parent.font
                        color: "#FFFFFF"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: backClicked()
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 30

            // Left Panel with Scrolling
            Rectangle {
                Layout.preferredWidth: parent.width * 0.25
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                Layout.fillHeight: true
                radius: 15
                color: "#121427"
                border.color: "#2daee6"
                border.width: 2

                Flickable {
                    anchors.fill: parent
                    anchors.margins: 16
                    contentHeight: operationsColumn.height
                    clip: true
                    
                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AsNeeded
                        width: 8
                        
                        contentItem: Rectangle {
                            radius: 4
                            color: "#555555"
                        }
                    }

                    ColumnLayout {
                        id: operationsColumn
                        width: parent.width
                        spacing: 12

                        Text {
                            text: "Operations"
                            font.family: "Roboto"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#FFFFFF"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Rectangle { Layout.fillWidth: true; height: 1; color: "#2daee6" }

                        // Insert
                        GroupBox {
                            Layout.fillWidth: true
                            background: Rectangle {
                                color: "#1a1d35"
                                radius: 6
                                border.color: "#2daee6"
                                border.width: 1
                            }

                            ColumnLayout {
                                anchors.fill: parent
                                spacing: 8

                                TextField {
                                    id: insertField
                                    Layout.fillWidth: true
                                    placeholderText: "Enter value to insert"
                                    font.pixelSize: 14
                                    font.family: "Roboto"
                                    color: "#FFFFFF"
                                    validator: IntValidator { }

                                    background: Rectangle {
                                        color: "#0d0f1f"
                                        radius: 6
                                        border.color: insertField.activeFocus ? "#2daee6" : "#3a3d55"
                                        border.width: 1
                                    }
                                }

                                OperationButton {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    text: "Insert"
                                    gradColor1: "#28a745"
                                    gradColor2: "#1e7e34"
                                    textColor: "#FFFFFF"
                                    hoverColor: "#34d058"
                                    
                                    onClicked: {
                                        if (insertField.text !== "") {
                                            var value = parseInt(insertField.text)
                                            if (!isNaN(value)) {
                                                var alreadyExists = treeManager.searchNode(value)
                                                if (alreadyExists) {
                                                    insertError.text = "Value already exists!"
                                                    insertError.visible = true
                                                    insertErrorTimer.start()
                                                } else {
                                                    treeManager.insertNode(value)
                                                    insertField.text = ""
                                                }
                                            }
                                        }
                                    }
                                }

                                Text {
                                    id: insertError
                                    Layout.fillWidth: true
                                    font.pixelSize: 12
                                    font.family: "Roboto"
                                    color: "#ef4444"
                                    horizontalAlignment: Text.AlignHCenter
                                    visible: false
                                }

                                Timer { 
                                    id: insertErrorTimer
                                    interval: 2000
                                    onTriggered: insertError.visible = false
                                }
                            }
                        }

                        // Update
                        GroupBox {
                            Layout.fillWidth: true
                            background: Rectangle {
                                color: "#1a1d35"
                                radius: 6
                                border.color: "#2daee6"
                                border.width: 1
                            }

                            ColumnLayout {
                                anchors.fill: parent
                                spacing: 8

                                
                                TextField {
                                    id: updateOldField
                                    Layout.fillWidth: true
                                    placeholderText: "Old Value"
                                    font.family: "Roboto"
                                    font.pixelSize: 14
                                    color: "#FFFFFF"
                                    validator: IntValidator { }
                                    background: Rectangle { 
                                        color: "#0d0f1f"
                                        radius: 6
                                        border.color: updateOldField.activeFocus ? "#2daee6" : "#3a3d55"
                                        border.width: 1
                                    }
                                }

                                TextField {
                                    id: updateNewField
                                    Layout.fillWidth: true
                                    placeholderText: "New Value"
                                    font.family: "Roboto"
                                    font.pixelSize: 14
                                    color: "#FFFFFF"
                                    validator: IntValidator { }
                                    background: Rectangle { 
                                        color: "#0d0f1f"
                                        radius: 6
                                        border.color: updateNewField.activeFocus ? "#2daee6" : "#3a3d55"
                                        border.width: 1
                                    }
                                }

                                OperationButton {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    text: "Update"
                                    gradColor1: "#0056b3"
                                    gradColor2: "#003d82"
                                    textColor: "#FFFFFF"
                                    hoverColor: "#0069d9"
                                    onClicked: {
                                        if (updateOldField.text === "" || updateNewField.text === "") return
                                        var oldVal = parseInt(updateOldField.text)
                                        var newVal = parseInt(updateNewField.text)
                                        if (isNaN(oldVal) || isNaN(newVal)) return
                                        var ok = treeManager.updateNode(oldVal, 1, newVal, "any")
                                        if (ok) {
                                            updateOldField.text = ""
                                            updateNewField.text = ""
                                        }
                                    }
                                }
                            }
                        }

                        // Delete
                        GroupBox {
                            Layout.fillWidth: true
                            background: Rectangle {
                                color: "#1a1d35"
                                radius: 6
                                border.color: "#2daee6"
                                border.width: 1
                            }

                            ColumnLayout {
                                anchors.fill: parent
                                spacing: 8

                                TextField {
                                    id: deleteField
                                    Layout.fillWidth: true
                                    placeholderText: "Enter value to delete"
                                    font.pixelSize: 14
                                    font.family: "Roboto"
                                    color: "#FFFFFF"
                                    validator: IntValidator { }
                                    background: Rectangle { 
                                        color: "#0d0f1f"
                                        radius: 6
                                        border.color: deleteField.activeFocus ? "#2daee6" : "#3a3d55"
                                        border.width: 1
                                    }
                                }

                                OperationButton {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    text: "Delete"
                                    gradColor1: "#0056b3"
                                    gradColor2: "#003d82"
                                    textColor: "#FFFFFF"
                                    hoverColor: "#0069d9"
                                    onClicked: {
                                        if (deleteField.text !== "") {
                                            var value = parseInt(deleteField.text)
                                            if (!isNaN(value)) {
                                                treeManager.deleteNode(value)
                                                deleteField.text = ""
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // Search
                        GroupBox {
                            Layout.fillWidth: true
                            background: Rectangle { 
                                color: "#1a1d35"
                                radius: 6
                                border.color: "#2daee6"
                                border.width: 1
                            }

                            ColumnLayout {
                                anchors.fill: parent
                                spacing: 8

                                TextField {
                                    id: searchField
                                    Layout.fillWidth: true
                                    placeholderText: "Enter value to search"
                                    font.pixelSize: 14
                                    font.family: "Roboto"
                                    color: "#FFFFFF"
                                    validator: IntValidator { }
                                    background: Rectangle { 
                                        color: "#0d0f1f"
                                        radius: 6
                                        border.color: searchField.activeFocus ? "#2daee6" : "#3a3d55"
                                        border.width: 1
                                    }
                                }

                                OperationButton {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    text: "Search"
                                    gradColor1: "#FFCC00"
                                    gradColor2: "#FFD54F"
                                    textColor: "#000000"
                                    hoverColor: "#ffd633"
                                    onClicked: {
                                        if (searchField.text !== "") {
                                            var value = parseInt(searchField.text)
                                            if (!isNaN(value)) {
                                                var found = treeManager.searchNode(value)
                                                searchResult.text = found ? "Found!" : "Not Found"
                                                searchResult.color = found ? "#38ef7d" : "#ef4444"
                                                searchResult.visible = true
                                                searchField.text = ""
                                                resultTimer.start()
                                            }
                                        }
                                    }
                                }

                                Text {
                                    id: searchResult
                                    Layout.fillWidth: true
                                    font.pixelSize: 14
                                    font.family: "Roboto"
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    color: "#FFFFFF"
                                    visible: false
                                }

                                Timer { id: resultTimer; interval: 2000; onTriggered: searchResult.visible = false }
                            }
                        }

                        // Traversals
                        GroupBox { 
                            Layout.fillWidth: true
                            background: Rectangle { 
                                color: "#1a1d35"
                                radius: 6
                                border.color: "#2daee6"
                                border.width: 1
                            }
                            
                            ColumnLayout { 
                                anchors.fill: parent
                                spacing: 8
                                
                                RowLayout { 
                                    Layout.fillWidth: true
                                    spacing: 8
                                    
                                    OperationButton { 
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 50
                                        text: "Inorder"
                                        gradColor1: "#FFCC00"
                                        gradColor2: "#FFD54F"
                                        textColor: "#000000"
                                        hoverColor: "#ffd633"
                                        onClicked: { 
                                            var result = treeManager.getInorderTraversal()
                                            traversalResult.text = "Inorder: " + result.join(", ")
                                            memoryModel.clear()
                                            for (var i=0;i<result.length;i++) memoryModel.append({value: result[i]})
                                            memoryPanel.visible = true
                                        }
                                    }
                                    
                                    OperationButton { 
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 50
                                        text: "Preorder"
                                        gradColor1: "#FFCC00"
                                        gradColor2: "#FFD54F"
                                        textColor: "#000000"
                                        hoverColor: "#ffd633"
                                        onClicked: { 
                                            var result = treeManager.getPreorderTraversal()
                                            traversalResult.text = "Preorder: " + result.join(", ")
                                            memoryModel.clear()
                                            for (var i=0;i<result.length;i++) memoryModel.append({value: result[i]})
                                            memoryPanel.visible = true
                                        }
                                    }
                                }
                                
                                OperationButton { 
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    text: "Postorder"
                                    gradColor1: "#FFCC00"
                                    gradColor2: "#FFD54F"
                                    textColor: "#000000"
                                    hoverColor: "#ffd633"
                                    onClicked: { 
                                        var result = treeManager.getPostorderTraversal()
                                        traversalResult.text = "Postorder: " + result.join(", ")
                                        memoryModel.clear()
                                        for (var i=0;i<result.length;i++) memoryModel.append({value: result[i]})
                                        memoryPanel.visible = true
                                    }
                                }

                                Text { 
                                    id: traversalResult
                                    Layout.fillWidth: true
                                    font.pixelSize: 14
                                    font.family: "Roboto"
                                    color: "#FFFFFF"
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }

                        OperationButton { 
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50
                            text: "Clear Tree"
                            gradColor1: "#dc3545"
                            gradColor2: "#bd2130"
                            textColor: "#FFFFFF"
                            hoverColor: "#e4606d"
                            onClicked: { 
                                treeManager.clearTree()
                                traversalResult.text = ""
                                memoryModel.clear()
                                memoryPanel.visible = false
                            }
                        }
                    }
                }
            }

            // Right Panel
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    spacing: 10
                    
                    Text {
                        text: "Zoom:"
                        color: "#FFFFFF"
                        font.pixelSize: 14
                        font.family: "Roboto"
                    }
                    
                    Button {
                        text: "−"
                        width: 35
                        height: 35
                        onClicked: canvas.scale = Math.max(0.5, canvas.scale - 0.1)
                        
                        background: Rectangle {
                            radius: 4
                            color: "#0056b3"
                            border.color: "#2daee6"
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#FFFFFF"
                            font.pixelSize: 18
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    
                    Text {
                        text: Math.round(canvas.scale * 100) + "%"
                        color: "#FFFFFF"
                        font.pixelSize: 14
                        font.family: "Roboto"
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                    }
                    
                    Button {
                        text: "+"
                        width: 35
                        height: 35
                        onClicked: canvas.scale = Math.min(2.0, canvas.scale + 0.1)
                        
                        background: Rectangle {
                            radius: 4
                            color: "#0056b3"
                            border.color: "#2daee6"
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#FFFFFF"
                            font.pixelSize: 18
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    
                    Button {
                        text: "Reset"
                        width: 60
                        height: 35
                        onClicked: { canvas.scale = 1.0; canvas.autoFit = false }
                        
                        background: Rectangle {
                            radius: 4
                            color: "#0056b3"
                            border.color: "#2daee6"
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#FFFFFF"
                            font.pixelSize: 12
                            font.family: "Roboto"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button {
                        id: fitButton
                        text: "Fit"
                        width: 60
                        height: 35
                        onClicked: { canvas.zoomToFit(); canvas.autoFit = false }

                        background: Rectangle { radius: 4; color: "#2daee6"; }
                        contentItem: Text { text: parent.text; color: "#000000"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                    }

                    CheckBox {
                        id: autoFitToggle
                        checked: true
                        text: "Auto-fit"
                        onCheckedChanged: { canvas.autoFit = checked }
                        contentItem: Text { color: "#FFFFFF" }
                    }
                    
                    Item { Layout.fillWidth: true }
                }

                Flickable {
                    id: flickableCanvas
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    // bind content size to dynamic canvas (TreeCanvas root rectangle) and scale
                    // add small padding so scrollbars don't clip the drawn edges
                    contentWidth: (canvas.width + 40) * canvas.scale
                    contentHeight: (canvas.height + 40) * canvas.scale

                    // Instantiate TreeCanvas without forcing width/height so it can compute its bounding box
                    TreeCanvas { 
                        id: canvas
                        // scale around center so zoom-to-fit keeps content centered
                        transformOrigin: Item.Center
                        // let TreeCanvas control its own width/height and scaling
                    }

                    // Helper to fit and center content in the Flickable viewport
                    function fitAndCenter() {
                        canvas.zoomToFit(flickableCanvas.width, flickableCanvas.height)
                        Qt.callLater(function() {
                            // center content
                            var contentW = (canvas.width || 0) * canvas.scale
                            var contentH = (canvas.height || 0) * canvas.scale
                            flickableCanvas.contentX = Math.max(0, (contentW - flickableCanvas.width)/2)
                            flickableCanvas.contentY = Math.max(0, (contentH - flickableCanvas.height)/2)
                        })
                    }
                    
                    // Ensure view recenters and fits after tree updates
                    Connections {
                        target: treeManager
                        function onNodeInserted(key) { Qt.callLater(fitAndCenter) }
                        function onNodeDeleted(key) { Qt.callLater(fitAndCenter) }
                        function onTreeCleared() { Qt.callLater(fitAndCenter) }
                        function onTreeUpdated() { Qt.callLater(fitAndCenter) }
                    }
                }

                Rectangle {
                    id: memoryPanel
                    Layout.fillWidth: true
                    height: visible ? 100 : 0
                    radius: 8
                    color: "#121427"
                    border.color: "#2daee6"
                    border.width: 2
                    visible: false

                    Flickable {
                        anchors.fill: parent
                        anchors.margins: 12
                        contentWidth: memoryRow.width
                        clip: true
                        
                        Row {
                            id: memoryRow
                            spacing: 8
                            
                            Repeater {
                                model: memoryModel
                                delegate: Rectangle {
                                    width: 64
                                    height: 64
                                    radius: 8
                                    color: "#1a1d35"
                                    border.color: "#2daee6"
                                    border.width: 1

                                    Text { 
                                        anchors.centerIn: parent
                                        text: model.value
                                        font.pixelSize: 18
                                        font.family: "Roboto"
                                        color: "#FFFFFF"
                                    }
                                }
                            }
                        }
                        
                        ScrollBar.horizontal: ScrollBar {
                            policy: ScrollBar.AsNeeded
                            height: 8
                        }
                    }
                }
            }
        }
    }

    component OperationButton: Button {
        id: opButton
        property string gradColor1: "#667eea"
        property string gradColor2: "#764ba2"
        property color textColor: "#000000"
        property color hoverColor: "#0056b3"

        background: Rectangle {
            radius: 8
            gradient: Gradient { 
                GradientStop { position: 0.0; color: opButton.gradColor1 } 
                GradientStop { position: 1.0; color: opButton.gradColor2 } 
            }

            scale: opButton.pressed ? 0.97 : (opButton.hovered ? 1.02 : 1.0)
            Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutBack } }
        }

        contentItem: Text {
            text: opButton.text
            font.pixelSize: 15
            font.family: "Roboto"
            font.bold: true
            color: opButton.textColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}