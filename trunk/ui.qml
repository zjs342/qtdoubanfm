import QtQuick 1.0
//import NativeQuickWidgets 1.0

Rectangle {
    property int mystate: widget.mystate
    property real opac1: 0.5
    property real opac2: 1
    property string picurl: widget.pic
    property string title: widget.title
    property string artist: widget.artist
    property string album: widget.album
    property string playsource: widget.playsource
    property string likesource: widget.likesource
    property int pbb: widget.pb
    property string cName: widget.cName
    property int cNum: widget.cNum
    property string cType: widget.cType
    property bool fdesktop: widget.fdesktop
    id: ui
    width: 420
    height: 180
    opacity: 1

    function updateData(type,num) {
        listModel.append({"name":widget.cName,"number":widget.cNum,"type":widget.cType})
        widget.updateData(type,num+1);
    } // slot

    function updateData2(type,a,text) {
        listModel2.append({"name":widget.cName,"number":widget.cNum,"type":widget.cType})
        widget.updateData2(widget.cType,a,text+1);
    } // slot


    MouseArea {
        id: mui
        hoverEnabled:true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        anchors.fill: parent
        onPressed: widget.movePos(mouseX,mouseY)
        onPositionChanged : if (pressed) {widget.moveThis()}
        //        onEntered: widget.enterw()
        //        onExited:  widget.leavew()
        //            if (mouse.button==Qt.RightButton)
        //                parent.color='red';}
        //        drag.target: ui
        //       drag.axis: Drag.XandYAxis
    }

    Image {
        id: pic
        x: 0
        y: 0
        width: 180
        height: 180
        smooth: true
        fillMode: Image.PreserveAspectFit
        source: widget.pic
        MouseArea{
            id:mpic
            hoverEnabled:true
            anchors.fill: parent
            onClicked: widget.openIt()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = 0.5
            onExited:  parent.opacity = 1
        }

    }

    Rectangle {
        id: rmin
        x: 355
        y: 0
        width: 30
        height: 30
        color: "#9dd6c5"

        Image {
            id: min
            width: 15
            height: 6
            anchors.verticalCenterOffset: 3
            anchors.centerIn: parent
            source: "qrc:image/min.png"
        }

        MouseArea{
            id:mmin
            hoverEnabled:true
            anchors.fill: parent
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onClicked: widget.minit()
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
    }

    Rectangle {
        id: rplay
        x: 320
        y: 0
        width: 30
        height: 30
        color: "#9dd6c5"

        Image {
            id: play
            width: 15
            height: 15
            anchors.centerIn: parent
            source: widget.playsource
        }
        MouseArea{
            id:mplay
            x: 0
            y: 0
            anchors.fill: parent
            //onPressed:
            hoverEnabled:true
            onClicked: widget.playPause()
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
    }

    Rectangle {
        id: rx
        x: 390
        y: 0
        width: 30
        height: 30
        color: "#9dd6c5"

        Image {
            id: x
            x: 15
            y: 15
            width: 15
            height: 15
            anchors.centerIn: parent
            smooth : true
            source: "qrc:image/x.png"
        }

        MouseArea{
            id:mx
            x: 0
            y: 0
            anchors.fill: parent
            onPressed: widget.quitIt()
            hoverEnabled:true
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
    }
    Rectangle {
        id: rsmall
        x: 285
        y: 0
        width: 30
        height: 30
        color: "#9dd6c5"

        Image {
            id: small
            width: 15
            height: 15
            anchors.centerIn: parent
            source: "qrc:image/small.png"
        }

        MouseArea {
            id: msmall
            drag.minimumY: -1000
            drag.minimumX: -1000
            drag.maximumY: 1000
            drag.maximumX: 1000
            hoverEnabled:true
            anchors.fill: parent
            onClicked: widget.enter()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
    }
    Image {
        id: like
        smooth : true
        x: 272
        y: 140
        width: 32
        height: 28
        source: widget.likesource
        MouseArea{
            id:mlike
            hoverEnabled:true
            x: 16
            y: 10
            width: 84
            height: 90
            anchors.fill: parent
            onClicked: widget.likeIt()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
        scale: mlike.pressed ? 1.2 : 1.00
        Behavior on scale { NumberAnimation{ duration: 100} }
    }


    Image {
        id: next
        smooth : true
        x: 366
        y: 138
        width: 32
        height: 32
        source: "qrc:image/next.png"
        MouseArea{
            id:mnext
            hoverEnabled:true
            anchors.fill: parent
            onClicked: widget.nextFile()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
        scale: mnext.pressed ? 1.2 : 1.00
        Behavior on scale { NumberAnimation{ duration: 100} }
    }

    Image {
        id: trash
        smooth : true
        x: 320
        y: 138
        width: 32
        height: 32
        source: "qrc:image/trash.png"
        MouseArea{
            id:mtrash
            hoverEnabled:true
            anchors.fill: parent
            onClicked: widget.trashIt()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = opac1
            onExited:  parent.opacity = opac2
        }
        scale: mtrash.pressed ? 1.2 : 1.00
        Behavior on scale { NumberAnimation{ duration: 100} }
    }

    Text {
        id: talbum
        x: 200
        y: 60
        width: 80
        height: 20
        text: album
        smooth: true
        font.family: "微软雅黑"
        font.pixelSize: 12
    }

    Text {
        id: tartist
        x: 200
        y: 30
        width: 80
        height: 80
        text: artist
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.NoWrap
        smooth: true
        font.family: "微软雅黑"
        font.pixelSize: 27
    }

    Text {
        id: ttitle
        x: 200
        y: 85
        width: 80
        height: 20
        color: "#049b68"
        text: title
        smooth: true
        font.family: "微软雅黑"
        font.pixelSize: 12
    }

    Text {
        id: line
        x: 200
        y: 30
        width: 180
        height: 20
        text: widget.title + "-" + widget.artist
        style: Text.Normal
        smooth: false
        horizontalAlignment: Text.AlignHCenter

        font.pointSize: 10
        font.family: "微软雅黑"

        opacity: 0
    }

    MouseArea {
        id: mchannel
        x: 340
        y: 70
        width: 80
        height: 40
        hoverEnabled:true
        onClicked: widget.setmystate2(mystate)
    }

    Rectangle {
        id: rchannel
        x: 420
        y: 72
        width: 0
        height: 40
        opacity: 0
        anchors.verticalCenter: parent.verticalCenter
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#9dd6c5"
            }

            GradientStop {
                position: 1
                color: "#ffffff"
            }
        }
        Behavior on x { NumberAnimation{ duration: 500} }
        Behavior on width { NumberAnimation{ duration: 500} }
        Behavior on opacity { NumberAnimation{ duration: 500} }
        Text {
            id: tchannel
            x: 28
            y: 23
            text: "\u6362\u53F0"
            font.family: "微软雅黑"
            anchors.centerIn: parent
            font.pixelSize: 15
        }
    }


     ProgressBar {
        id:pb
        x: 200
        y: 100
        width: 210
        height: 4
        minimum: 0
        maximum: 999
        value: pbb
    }

    Text {
        id: ttime
        x: 340
        y: 110
        width: 100
        height: 20
        text: widget.ttime
        font.pixelSize: 12
    }

    Rectangle {
        id: rperson
        x: -100
        y: 20
        width: 100
        height: 30
        MouseArea{
            id:mperson
            hoverEnabled:true
            anchors.fill: parent
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onClicked: widget.changeChannel("public",0),listModel.clear(),listModel2.clear(),tdianbo.focus = false;
            onEntered: parent.border.color = "gold"
            onExited:  parent.border.color = "white"
        }
        Text {
            id: tperson
            text: "\u79C1\u4EBA\u5146\u8D6B"
            font.family: "微软雅黑"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            font.pixelSize: 16
        }
        color: mperson.pressed ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
        Behavior on color { ColorAnimation{ duration: 150} }
        opacity: 0
        scale: mperson.pressed ? 1.1 : 1.00
        Behavior on scale { NumberAnimation{ duration: 150} }
    }

    Rectangle {
        id: rpublic
        x: -100
        y: 60
        width: 100
        height: 30
        MouseArea{
            id:mpublic
            hoverEnabled:true
            anchors.fill: parent
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
//            onClicked:listModel.append({"name":"spring","number":"003"})
            onClicked: listModel.clear(),listModel2.clear(),widget.updateData("public",0),tdianbo.focus = false;
            onEntered: parent.border.color = "gold"
            onExited:  parent.border.color = "white"
        }
        Text {
            id: tpublic
            text: "\u516C\u5171\u5146\u8D6B"
            font.family: "微软雅黑"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
            font.pixelSize: 16
        }
        color: mpublic.pressed ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
        Behavior on color { ColorAnimation{ duration: 150} }
        opacity: 0
        scale: mpublic.pressed ? 1.1 : 1.00
        Behavior on scale { NumberAnimation{ duration: 150} }
    }

    Rectangle {
        id: rdj
        x: -100
        y: 100
        width: 100
        height: 30
        MouseArea{
            id:mdj
            hoverEnabled:true
            anchors.fill: parent
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onClicked: listModel.clear(),listModel2.clear(),widget.updateData("dj",0),tdianbo.focus = false;
            onEntered: parent.border.color = "gold"
            onExited:  parent.border.color = "white"
        }
        Text {
            id: tdj
            text: "DJ\u5146\u8D6B"
            font.family: "微软雅黑"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            font.pixelSize: 16
        }

        color: mdj.pressed ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
        Behavior on color { ColorAnimation{ duration: 150} }
        opacity: 0
        scale: mdj.pressed ? 1.1 : 1.00
        Behavior on scale { NumberAnimation{ duration: 150} }
    }

    Rectangle {
        id: rdianbo
        x: -100
        y: 140
        width: 100
        height: 30
        color: "#9dd6c5"
        opacity: 0
        MouseArea{
            id:mdianbo
            hoverEnabled:true
            anchors.fill: parent
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onClicked:
                if (!tdianbo.activeFocus) {
                    tdianbo.forceActiveFocus();
                    tdianbo.openSoftwareInputPanel();
                    tdianbo.text="";
                } else {
                    //tdianbo.focus = false;
                }
            onEntered: parent.border.color = "gold"
            onExited:  parent.border.color = "white"
        }
        TextInput {
            id: tdianbo
            text: "\u70B9\u64AD"
            font.pixelSize: 16
            font.family: "微软雅黑"
            anchors.centerIn: parent
            horizontalAlignment: TextInput.AlignHCenter
            onAccepted: listModel.clear(),listModel2.clear(),widget.search(text)
        }
        //Keys.onEnterPressed:  console.log("move rec"),widget.search(tdianbo.text)
        scale: mdianbo.pressed ? 1.1 : 1.00
        Behavior on scale { NumberAnimation{ duration: 150} }
    }
    Rectangle {
        id: rback
        x: 420
        y: 150
        width: 80
        height: 30
        opacity: 0

        Text {
            id: tback
            text: "\u8FD4\u56DE"
            anchors.centerIn: parent
            font.pixelSize: 16
            font.family: "微软雅黑"
        }
        MouseArea{
            id:mback
            hoverEnabled:true
            anchors.fill: parent
            onClicked: widget.setmystate2(mystate)
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.border.color = "gold"
            onExited:  parent.border.color = "white"
        }
        color: mback.pressed ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
        Behavior on color { ColorAnimation{ duration: 150} }
        scale: mback.pressed ? 1.1 : 1.00
        Behavior on scale { NumberAnimation{ duration: 150} }
    }

    ListView{
        id: listview1
        x: 0
        y: 0  //视图
        width:100; height:180
        opacity: 0
        model:listModel  //关联数据模型
        delegate:delegate  //关联代理
        //highlight:highlight  //关联高亮条
        //highlightFollowsCurrentItem: false
        //currentIndex: 2
        //keyNavigationWraps: true
        //orientation: ListView.Horizontal
        //Component.onCompleted: positionViewAtIndex(count-1, ListView.Beginning)
        //Keys.onPressed :console.log(currentItem.data +" is selected!")
        //Keys.onEnterPressed:console.log(currentItem.data +" is onEnterPressed!")
        focus:true  //可以获得焦点，这样就可以响应键盘了
        //highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: 70; preferredHighlightEnd: 70
        //onCurrentIndexChanged: root.current = currentIndex
    }

    ListModel{  //数据模型
        id:listModel
    }

    Component{     //代理
        id:delegate
        Item{
            id:wrapper; width:100; height:30
            Rectangle{
                id: background
                //border.color: "gray"
                width: 100
                height: 30
                x:5; y:5
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text:name//+"<b>MHz</b>"
                    font.family: "微软雅黑"
                }
                //color: ma.enabled ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
                Behavior on color { ColorAnimation{ duration: 150} }
                scale: ma.pressed ? 1.1 : 1.00
                Behavior on scale { NumberAnimation{ duration: 150} }
            }
            MouseArea{
                id:ma
                hoverEnabled:true
                anchors.fill: parent
                //            onPressed: widget.mystate(2,3)
                //          onReleased: widget.mystate(2,1)
                onEntered: background.color="#9dd6c5"
                onExited:  background.color="#ffffff"
                onClicked: listModel2.clear(),widget.updateData2(widget.cType,number,0);
            }
            //Text{text:"<b>Number:</b>"+number}

        }
    }

    Component{   //高亮条
        id:highlight
        Rectangle{
            color:"#9dd6c5";
            radius:5
            //y: listview1.currentItem.y;
            // Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
            /*      MouseArea{
                hoverEnabled:true
                anchors.fill: parent
                //            onPressed: widget.mystate(2,3)
                //          onReleased: widget.mystate(2,1)
                onEntered: parent.color = "gold"
                onExited:  parent.color = "gold"
            }
        */
        }
    }

    ListView {
        id: listview2
        x: 0
        y: 0
        width: 100
        height: 180
        opacity: 0
        model:listModel2  //关联数据模型
        delegate:delegate2  //关联代理
        focus:true  //可以获得焦点，这样就可以响应键盘了
        preferredHighlightBegin: 70; preferredHighlightEnd: 70
    }

    ListModel{  //数据模型
        id:listModel2
    }

    Component{     //代理
        id:delegate2
        Item{
            id:wrapper; width:100; height:30
            Rectangle{
                id: background2
                //border.color: "gray"
                width: 100
                height: 30
                x:5; y:5
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text:name//+"<b>MHz</b>"
                    font.family: "微软雅黑"
                }
                //color: ma.enabled ? Qt.darker("#9dd6c5", 1.2) : "#9dd6c5"
                Behavior on color { ColorAnimation{ duration: 150} }
                scale: ma2.pressed ? 1.1 : 1.00
                Behavior on scale { NumberAnimation{ duration: 150} }
            }
            MouseArea{
                id:ma2
                hoverEnabled:true
                anchors.fill: parent
                //            onPressed: widget.mystate(2,3)
                //          onReleased: widget.mystate(2,1)
                onEntered: background2.color="#9dd6c5"
                onExited:  background2.color="#ffffff"
                onClicked: widget.changeChannel(widget.cType,number),console.log(widget.cType + number + name)
            }
            //Text{text:"<b>Number:</b>"+number}

        }
    }

    Rectangle {
        id: rdesktop
        x: 0
        y: 50
        width: 30
        height: 30
        color: "#9dd6c5"
        opacity: 0.1

        Image {
            id: desktop
            width: 15
            height: 15
            anchors.centerIn: parent
            source: "qrc:image/rss_32x32.png"
        }

        MouseArea {
            id: mdesktop
            opacity: 1
            anchors.fill: parent
            hoverEnabled:true
            onClicked: widget.Mdesktop(widget.fdesktop)//,console.log("desktop")
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = 1
            onExited:  parent.opacity = 0.1
        }
    }

    Rectangle {
        id: rdownload
        x: 0
        y: 100
        width: 30
        height: 30
        color: "#9dd6c5"
        opacity: 0.1

        Image {
            id: download
            width: 15
            height: 15
            anchors.centerIn: parent
            source: "qrc:image/down.png"
        }

        MouseArea {
            id: mdownload
            opacity: 1
            anchors.fill: parent
            hoverEnabled:true
            onClicked: widget.downloadSong()
            //            onPressed: widget.mystate(2,3)
            //          onReleased: widget.mystate(2,1)
            onEntered: parent.opacity = 1
            onExited:  parent.opacity = 0.1
        }
    }
    states: [
        State {
            name: "normal"
            when: mystate==0
            PropertyChanges {
                target: ui
                opac1:0.5
                opac2:1
            }
            PropertyChanges {
                target: line
                opacity: 0
            }

            PropertyChanges {
                target: rperson
                opacity: 0
            }

            PropertyChanges {
                target: rpublic
                opacity: 0
            }

            PropertyChanges {
                target: rdj
                opacity: 0
            }
            PropertyChanges {
                target: mchannel
                x: 340
                y: 70
                opacity: 1
                onEntered: rchannel.opacity = 1,rchannel.width=80,rchannel.x=340
                onExited:  rchannel.opacity = 0,rchannel.width=0,rchannel.x=420
            }

            PropertyChanges {
                target: pic
                opacity: 1
            }

            PropertyChanges {
                target: rmin
                opacity: 1
            }

            PropertyChanges {
                target: rplay
                opacity: 1
            }

            PropertyChanges {
                target: rx
                opacity: 1
            }

            PropertyChanges {
                target: rsmall
                opacity: 1
            }

            PropertyChanges {
                target: like
                opacity: 1
            }

            PropertyChanges {
                target: next
                opacity: 1
            }

            PropertyChanges {
                target: trash
                opacity: 1
            }

            PropertyChanges {
                target: talbum
                opacity: 1
            }

            PropertyChanges {
                target: tartist
                opacity: 1
            }

            PropertyChanges {
                target: ttitle
                opacity: 1
            }

            PropertyChanges {
                target: ttime
                opacity: 1
            }

            PropertyChanges {
                target: rback
                opacity: 0
            }

            PropertyChanges {
                target: rchannel
                opacity: 0
            }
        },
        State {
            name: "small1"
            when: mystate==1
            PropertyChanges {
                target: ui
                opac1:1
                opac2:0.1
                width: 180
            }

            PropertyChanges {
                target: pb
                opacity: 0
            }

            PropertyChanges {
                target: rmin
                x: 100
                y: 0
                opacity: 0.1
            }

            PropertyChanges {
                target: rplay
                x: 50
                y: 0
                opacity: 0.1
            }

            PropertyChanges {
                target: rx
                x: 150
                y: 0
                opacity: 0.1
            }

            PropertyChanges {
                target: like
                x: 0
                y: 147
                opacity: 0.1
            }

            PropertyChanges {
                target: next
                x: 148
                y: 145
                opacity: 0.1
            }

            PropertyChanges {
                target: trash
                x: 74
                y: 145
                opacity: 0.1
            }

            PropertyChanges {
                target: talbum
                opacity: 0
            }

            PropertyChanges {
                target: tartist
                opacity: 0
            }

            PropertyChanges {
                target: ttitle
                opacity: 0
            }

            PropertyChanges {
                target: line
                x: 0
                y: 165
                opacity: 1
            }

            PropertyChanges {
                target: rsmall
                x: 0
                y: 0
                opacity: 0.1
            }

            PropertyChanges {
                target: pic
                x: 15
                y: 15
                width: 150
                height: 150
                opacity: 1
            }

            PropertyChanges {
                target: small
                source: "qrc:image/big.png"
            }

            PropertyChanges {
                target: mchannel
                x: 100
                y: 70
                opacity: 1
                onEntered: rchannel.opacity = 1,rchannel.width=80,rchannel.x=100
                onExited:  rchannel.opacity = 0,rchannel.width=0,rchannel.x=180
            }

            PropertyChanges {
                target: rperson
                opacity: 0
            }

            PropertyChanges {
                target: rpublic
                opacity: 0
            }

            PropertyChanges {
                target: rdj
                opacity: 0
            }

            PropertyChanges {
                target: rchannel
                x: 180
                opacity: 0
            }

            PropertyChanges {
                target: ttime
                opacity: 0
            }

            PropertyChanges {
                target: rback
                opacity: 0
            }
        },
        State {
            name: "channel"
            when: mystate==2
            PropertyChanges {
                target: ui
                width: 420
                opac1:0.5
                opac2:1
            }
            PropertyChanges {
                target: pb
                opacity: "0"
            }

            PropertyChanges {
                target: rmin
                x: "100"
                y: "0"
                opacity: 0
            }

            PropertyChanges {
                target: rplay
                x: "50"
                y: "0"
                opacity: 0
            }

            PropertyChanges {
                target: rx
                x: 390
                y: "0"
                opacity: 1
            }

            PropertyChanges {
                target: like
                x: "0"
                y: "147"
                opacity: 0
            }

            PropertyChanges {
                target: next
                x: "148"
                y: "145"
                opacity: 0
            }

            PropertyChanges {
                target: trash
                x: "74"
                y: "145"
                opacity: 0
            }

            PropertyChanges {
                target: talbum
                opacity: "0"
            }

            PropertyChanges {
                target: tartist
                opacity: "0"
            }

            PropertyChanges {
                target: ttitle
                opacity: "0"
            }

            PropertyChanges {
                target: line
                x: "0"
                y: "165"
                opacity: 0
            }

            PropertyChanges {
                target: rsmall
                x: "0"
                y: "0"
                opacity: 0
            }

            PropertyChanges {
                target: pic
                x: "15"
                y: "15"
                width: "150"
                height: "150"
                opacity: 0
            }

            PropertyChanges {
                target: small
                source: "qrc:image/big.png"
            }

            PropertyChanges {
                target: mchannel
                opacity: "0"
            }

            PropertyChanges {
                target: rperson
                x: 20
                y: 20
                opacity: 1
            }

            PropertyChanges {
                target: rpublic
                x: 20
                y: 60
                opacity: 1
            }

            PropertyChanges {
                target: rdj
                x: 20
                y: 100
                opacity: 1
            }

            PropertyChanges {
                target: ttime
                opacity: 0
            }

            PropertyChanges {
                target: rback
                x: 339
                y: 149
                opacity: 1
            }

            PropertyChanges {
                target: mpic
                opacity: 1
            }

            PropertyChanges {
                target: rchannel
                opacity: 0
            }

            PropertyChanges {
                target: tdianbo
                x: 19
                y: 140
                opacity: 1
            }

            PropertyChanges {
                target: rdianbo
                x: 20
                opacity: 1
            }

            PropertyChanges {
                target: listview1
                x: 130
                y: 0
                opacity: 1
            }

            PropertyChanges {
                target: listview2
                x: 235
                y: 0
                opacity: 1
            }

        }
    ]
    transitions: Transition {
        //     from: ""; to: "down"; reversible: true
        ParallelAnimation {
            NumberAnimation { properties: "opacity,x,y,width,height"; duration: 500; easing.type: Easing.InOutQuad }
        }
    }

}
