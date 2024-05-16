import QtQuick 2.15
import QtWebView

WebView {
        id: webView
        anchors.fill: parent
        url: "https://youtube.fr"
        onLoadingChanged: {
            if (loadRequest.errorString)
                console.error(loadRequest.errorString);
        }
    }
