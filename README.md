# HtmlGen

This library provide possibility to easy generate html page for esp8266.

## Usage

```c++
  HtmlPage *page = new HtmlPage();
  page->getHeader()->setTitle("Welcome My Page");
  HtmlTag* htmlTag = new HtmlTag("meta");
  htmlTag->getAttributes()->append("name", "viewport");
  htmlTag->getAttributes()->append("content", "width=device-width");
  page->getHeader()->append(htmlTag);

  HtmlStyleGroup* group = page->getHeader()->getStyle()->createGroup(".tabs td");
  group->append("width", "50%");
  group = page->getHeader()->getStyle()->createGroup(".htable");
  group->append("border", "1px solid #cdd0d4");
  group->append("width", "300px");
  group = page->getHeader()->getStyle()->createGroup(".hheader");
  group->append("background-color", "#cdd0d4");
  group->append("width", "300px");
  group = page->getHeader()->getStyle()->createGroup(".button");
  group->append("width", "100px");
  group->append("height", "40px");

  HtmlTable *tabs = new HtmlTable(2);
  tabs->append();
  tabs->getAttributes()->append("class", "tabs");
  tabs->getStyle()->append("width", "300px");
  tabs->getStyle()->append("background-color", "#DAF7A6");
  tabs->getCellStyle(0, pageIndex)->append("background-color", "#33ff6e");
  tabs->setCell(0, 0, new HtmlLink("/", "Overview"));
  tabs->setCell(0, 1, new HtmlLink("/network.html", "Network"));
  page->getHeader()->append(tabs);

  HtmlTable *tblOverview = new HtmlTable(2);
  tblOverview->append(10);
  tblOverview->getStyle()->append("width", "300px");
  tblOverview->getCellAttribute(0, 0)->append("colspan", 2);
  tblOverview->getCellAttribute(0, 0)->append("align", "center");
  tblOverview->getStyle()->append("border", "1px solid #cdd0d4");
  tblOverview->getCellStyle(0, 0)->append("background-color", "#cdd0d4");
  tblOverview->setCell(0, 0, "System");

  tblOverview->setCell(1, 0, "SSID:");
  if (WiFi.getMode()==WIFI_STA){
    tblOverview->setCell(1, 1, WiFi.SSID().c_str());
  } else {
    tblOverview->setCell(1, 1, deviceName);
  }
    
  tblOverview->setCell(2, 0, "Mode:");
  const char* modes[] = { "NULL", "STA", "AP", "STA+AP" };
  tblOverview->setCell(2, 1, modes[WiFi.getMode()]);
  tblOverview->setCell(3, 0, "Ip:");
  if (WiFi.getMode()==WIFI_STA){
    tblOverview->setCell(3, 1, WiFi.localIP().toString().c_str());  
  } else {
    tblOverview->setCell(3, 1, WiFi.softAPIP().toString().c_str());  
  }
  tblOverview->setCell(4, 0, "Mac:");
  tblOverview->setCell(4, 1, WiFi.macAddress().c_str());
  tblOverview->setCell(5, 0, "Heap memory:");
  tblOverview->setCell(5, 1, (int)ESP.getFreeHeap());
  page->append(tblOverview); 

  char html_overiview[1900];
  html_overiview[0] = '\0';
  htmlPage->print(html_overiview);
  server.send(200, "text/html", html_overiview);
  delete htmlPage;
```