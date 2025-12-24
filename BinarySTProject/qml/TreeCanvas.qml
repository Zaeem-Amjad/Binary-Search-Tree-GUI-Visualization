import QtQuick

Rectangle {
    id: canvasContainer
    property bool autoFit: true
    radius: 15
    color: "#121427"
    border.color: "#2daee6"
    border.width: 2

    // sensible implicit size so the canvas is visible before first paint
    implicitWidth: 800
    implicitHeight: 400

    // Allow smooth animated scaling when auto-fit or user zooms
    Behavior on scale { NumberAnimation { duration: 300; easing.type: Easing.OutQuad } }

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.margins: 20

        property var treeData: []
        property var pendingInsertKeys: []

        function scheduleInsertAnimation(key) {
            if (!pendingInsertKeys) pendingInsertKeys = []
            pendingInsertKeys.push(key)
            repaintTimer.restart()
        }

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()

            // Get tree structure from TreeManager
            treeData = treeManager.getTreeStructure()

            if (treeData.length === 0) {
                // ensure container has minimum size even when empty
                canvasContainer.width = Math.max(canvasContainer.width || 800, 800)
                canvasContainer.height = Math.max(canvasContainer.height || 400, 400)

                // Draw empty tree message on visible area
                ctx.fillStyle = "#9aa3b2"
                ctx.font = "20px 'Segoe UI'"
                ctx.textAlign = "center"
                ctx.fillText("Tree is empty. Insert some nodes!", canvasContainer.width/2 - (translateX||0), canvasContainer.height/2 - (translateY||0))
                return
            }

            // Build inorder index map to give stable left-to-right placement
            var inorder = treeManager.getInorderTraversal()
            var indexMap = {}
            for (var i = 0; i < inorder.length; ++i) { indexMap[inorder[i]] = i }

            // Layout constants (adaptive)
            var PADDING = 40
            var minNodeSpacing = 60
            var maxNodeSpacing = 160
            var LEVEL_V_SPACING = 120 // vertical spacing per level

            // determine horizontal spacing based on available width and number of nodes
            var numNodes = Math.max(1, inorder.length)
            // prefer available parent width (the Flickable viewport) if possible
            var flick = canvasContainer.parent
            var viewportW = (flick && flick.width) ? flick.width : 1000
            var availableW = Math.max(800, viewportW - 40)
            var NODE_H_SPACING = Math.floor(Math.min(maxNodeSpacing, Math.max(minNodeSpacing, availableW / Math.max(1, numNodes - 1))))

            // collision avoidance: expand spacing until adjacent nodes don't overlap
            var NODE_RADIUS = 30
            var MIN_GAP = 10
            function nodesOverlapWithSpacing(spacing) {
                for (var ii = 1; ii < inorder.length; ++ii) {
                    var leftX = PADDING + (ii-1) * spacing
                    var rightX = PADDING + ii * spacing
                    if (Math.abs(rightX - leftX) < (2*NODE_RADIUS + MIN_GAP)) return true
                }
                return false
            }

            var attempt = 0
            while (nodesOverlapWithSpacing(NODE_H_SPACING) && NODE_H_SPACING < maxNodeSpacing && attempt < 40) {
                NODE_H_SPACING += 8
                attempt++
            }

            // Compute positions and bounding box
            var minX = Number.POSITIVE_INFINITY, maxX = Number.NEGATIVE_INFINITY
            var minY = Number.POSITIVE_INFINITY, maxY = Number.NEGATIVE_INFINITY

            var positions = {}
            for (var i = 0; i < treeData.length; ++i) {
                var n = treeData[i]
                var key = n.key
                if (key === undefined || key === null) continue
                var idx = (key in indexMap) ? indexMap[key] : i
                var px = PADDING + idx * NODE_H_SPACING
                var py = PADDING + n.level * LEVEL_V_SPACING
                positions[key] = { x: px, y: py }
                if (px < minX) minX = px
                if (px > maxX) maxX = px
                if (py < minY) minY = py
                if (py > maxY) maxY = py
            }

            // safety fallback
            if (!isFinite(minX)) { minX = PADDING; maxX = PADDING + NODE_H_SPACING }
            if (!isFinite(minY)) { minY = PADDING; maxY = PADDING + LEVEL_V_SPACING }

            // Expand canvasContainer to fit content with padding
            var requiredW = (maxX - minX) + (2 * PADDING)
            var requiredH = (maxY - minY) + (2 * PADDING)
            var minW = 800
            var minH = 400
            // apply sizes on the outer container so Flickable sees changes
            canvasContainer.width = Math.max(minW, requiredW)
            canvasContainer.height = Math.max(minH, requiredH)

            // Determine translation to center content horizontally and keep some top margin
            var translateX = Math.round((canvasContainer.width - (maxX - minX)) / 2 - minX)
            var translateY = Math.round(80 - minY) // root placed 80px from top

            ctx.translate(translateX, translateY)

            // Draw connections using parent pointers (thicker navy lines)
            ctx.strokeStyle = "#003366"
            ctx.lineWidth = 3
            for (var k = 0; k < treeData.length; ++k) {
                var cn = treeData[k]
                var parentKey = cn.parent
                if (parentKey !== undefined && parentKey !== -1) {
                    var parentPos = positions[parentKey]
                    var childPos = positions[cn.key]
                    if (parentPos && childPos) {
                        ctx.beginPath()
                        ctx.moveTo(parentPos.x, parentPos.y)
                        ctx.lineTo(childPos.x, childPos.y)
                        ctx.stroke()
                    }
                }
            }

            // Draw nodes with 3px white border
            for (var i = 0; i < treeData.length; ++i) {
                var currentNode = treeData[i]
                var key = currentNode.key
                if (key === undefined || key === null) continue
                var pos = positions[key]
                if (!pos) continue
                var x = pos.x
                var y = pos.y

                // Node radial gradient
                var gradient = ctx.createRadialGradient(x, y, 0, x, y, 30)
                if (currentNode.color === "red") {
                    gradient.addColorStop(0, "#ff8a80")
                    gradient.addColorStop(1, "#ef4444")
                } else if (currentNode.color === "black") {
                    gradient.addColorStop(0, "#b0b0b0")
                    gradient.addColorStop(1, "#2d3436")
                } else {
                    gradient.addColorStop(0, "#88aaff")
                    gradient.addColorStop(1, "#0984E3")
                }

                ctx.fillStyle = gradient
                ctx.beginPath()
                ctx.arc(x, y, 30, 0, Math.PI * 2)
                ctx.fill()

                // Draw node border thick white
                ctx.strokeStyle = "#ffffff"
                ctx.lineWidth = 3
                ctx.stroke()

                // Draw node value - ensure it is a number
                var display = (typeof key === 'number') ? key.toString() : String(key)
                ctx.fillStyle = "#ffffff"
                ctx.font = "bold 16px 'Segoe UI'"
                ctx.textAlign = "center"
                ctx.textBaseline = "middle"
                ctx.fillText(display, x, y)
            }

            // Handle pending insert animations now that positions & translation are known
            if (pendingInsertKeys && pendingInsertKeys.length > 0) {
                for (var pi = 0; pi < pendingInsertKeys.length; ++pi) {
                    var ik = pendingInsertKeys[pi]
                    var ppos = positions[ik]
                    if (!ppos) continue
                    // translate positions into container coordinates (same transform used for drawing)
                    var animX = ppos.x + translateX
                    var animY = ppos.y + translateY
                    // give each inserting node a unique random X start offset so fall animation looks natural
                    var startX = animX + (Math.random() * 240 - 120)
                    var startY = -60 - Math.random() * 120
                    animModel.append({ key: ik, x: startX, targetX: animX, targetY: animY, startY: startY })
                }
                pendingInsertKeys = []
            }

            // Auto zoom-to-fit if enabled
            if (canvasContainer.autoFit) {
                var flickW = (flick && flick.width) ? flick.width : canvasContainer.width
                var flickH = (flick && flick.height) ? flick.height : canvasContainer.height
                if (flickW > 0 && flickH > 0) {
                    var scaleX = flickW / canvasContainer.width
                    var scaleY = flickH / canvasContainer.height
                    var targetScale = Math.min(scaleX, scaleY)
                    // shrink slightly to leave margin so nodes/edges don't touch clipping bounds
                    targetScale *= 0.95
                    targetScale = Math.max(0.25, Math.min(1.4, targetScale))
                    canvasContainer.scale = targetScale
                }
            }

            // Restore any transforms for safety
            ctx.resetTransform()
        }

        Timer {
            id: repaintTimer
            interval: 50
            repeat: false
            onTriggered: canvas.requestPaint()
        }

        // Model for animated falling nodes
        ListModel { id: animModel }

        // Overlay animation layer
        Item {
            id: animationLayer
            anchors.fill: parent
            z: 10

            Repeater {
                model: animModel
                delegate: Item {
                    id: animItem
                    property int nodeKey: model.key
                    width: 56; height: 56
                    x: model.x - width/2
                    y: model.startY
                    scale: 0.6
                    opacity: 1.0

                    // Glow ring (simple animated rectangle with radial look)
                    Rectangle {
                        id: glow
                        anchors.centerIn: parent
                        width: parent.width * 1.8; height: parent.height * 1.8
                        radius: width/2
                        color: "#88cfff"
                        opacity: 0.0
                        scale: 0.8
                    }

                    // Node circle
                    Rectangle {
                        id: nodeRect
                        anchors.centerIn: parent
                        width: parent.width; height: parent.height
                        radius: width/2
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#88aaff" }
                            GradientStop { position: 1.0; color: "#6b5cff" }
                        }
                        border.color: "#ffffff"
                        border.width: 3
                    }

                    Text {
                        anchors.centerIn: parent
                        text: model.key
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    SequentialAnimation {
                        id: animSequence
                        // animate both x and y to land at targetX,targetY
                        ParallelAnimation {
                            NumberAnimation { target: animItem; property: "x"; to: model.targetX - width/2; duration: 900; easing.type: Easing.OutCubic }
                            NumberAnimation { target: animItem; property: "y"; to: model.targetY; duration: 900; easing.type: Easing.OutBounce }
                        }
                        ParallelAnimation {
                            NumberAnimation { target: animItem; property: "scale"; to: 1.0; duration: 500; easing.type: Easing.OutCubic }
                            NumberAnimation { target: animItem; property: "opacity"; to: 1.0; duration: 300 }
                            NumberAnimation { target: glow; property: "opacity"; from: 0.0; to: 0.7; duration: 300 }
                            NumberAnimation { target: glow; property: "scale"; from: 0.8; to: 1.2; duration: 500 }
                        }
                        ScriptAction { script: {
                            // remove animated item after finishing
                            var idx = -1;
                            for (var i=0;i<animModel.count;i++) {
                                var it = animModel.get(i);
                                if (it.key === model.key && it.targetY === model.targetY) { idx = i; break; }
                            }
                            if (idx !== -1) animModel.remove(idx);
                            repaintTimer.restart();
                        }}
                    }

                    Component.onCompleted: {
                        animSequence.start()
                    }
                }
            }
        }

        Connections {
            target: treeManager

            function onNodeInserted(key) {
                // schedule animation; actual anim coords computed during paint
                canvas.scheduleInsertAnimation(key)
                repaintTimer.restart()
            }

            function onNodeDeleted(key) {
                repaintTimer.restart()
            }

            function onTreeCleared() {
                repaintTimer.restart()
            }

            function onTreeUpdated() {
                repaintTimer.restart()
            }
        }
    }

    // expose zoomToFit on the root component so parent QML can call canvas.zoomToFit()
    function zoomToFit(viewW, viewH) {
        var flick = canvasContainer.parent
        var flickW = (viewW && viewW > 0) ? viewW : ((flick && flick.width) ? flick.width : canvasContainer.width)
        var flickH = (viewH && viewH > 0) ? viewH : ((flick && flick.height) ? flick.height : canvasContainer.height)
        if (flickW > 0 && flickH > 0) {
            // ensure we account for canvas margins (20 left/right/top/bottom)
            var effectiveContentW = Math.max(1, canvasContainer.width - 40)
            var effectiveContentH = Math.max(1, canvasContainer.height - 40)
            var scaleX = flickW / effectiveContentW
            var scaleY = flickH / effectiveContentH
            var targetScale = Math.min(scaleX, scaleY)
            // shrink slightly to leave margin so nodes/edges don't touch clipping bounds
            targetScale *= 0.95
            targetScale = Math.max(0.25, Math.min(1.4, targetScale))
            canvasContainer.scale = targetScale
        }
    }

    // Animated background dots
    Repeater {
        model: 12
        Rectangle {
            width: 4; height: 4; radius: 2
            color: "#2daee6"
            opacity: 0.12
            x: Math.random() * canvasContainer.width
            y: Math.random() * canvasContainer.height

            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { from: -10; to: canvasContainer.height + 10; duration: 4000 + Math.random() * 3000 }
                ScriptAction { script: parent.y = -10 }
            }
        }
    }
}