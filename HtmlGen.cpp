/*
html.cpp - Library for easy generate Html page.
Created by Yuri Tarzimanov, November 06, 2017.
Released into the public domain.
*/

#include "HtmlGen.h"
#include "XmlGen.h"
#include <stdlib_noniso.h>

#define PAGE_FOOTER "footer"
#define PAGE_HEADER "header"
#define PAGE_BODY "body"
#define PAGE_TITLE "title"

#define ATT_DISABLED "disabled"
#define ATT_TYPE "type"
#define ATT_CHECKBOX "checkbox"
#define ATT_HIDDEN "hidden"
#define ATT_PASSWORD "password"
#define ATT_TEXT "text"
#define ATT_STEP "step"
#define ATT_MAX "max"
#define ATT_MIN "min"
#define ATT_SELECT "select"
#define ATT_STYLE "style"
#define ATT_SELECTED "selected"
#define ATT_OPTION "option"
#define ATT_NUMBER "number"
#define ATT_VALUE "value"
#define ATT_CHECKED "checked"
#define ATT_ACTION "action"
#define ATT_METHOD "method"
#define ATT_GET_METHOD "get"
#define ATT_POST_METHOD "post"
#define ATT_HREF "href"

#define TAG_BUTTON "button"
#define TAG_STYLE "style"
#define TAG_INPUT "input"
#define TAG_NAME "name"
#define TAG_ID "id"
#define TAG_TITLE "title"
#define TAG_TABLE "table"
#define TAG_FORM "form"
#define TAG_A "a"
#define TAG_TD "td"
#define TAG_TR "tr"

class HtmlTagAccess : public XmlTag
{
  public:
	void print(char *text)
	{
		XmlTag::print(text);
	}
};

void HtmlStyleAttribute::print(char *text)
{
	strcat(text, key);
	strcat(text, ":");
	strcat(text, val);
	strcat(text, ";");
}

HtmlStyleAttribute::HtmlStyleAttribute(char *key, char *val)
{
	this->key = new char[strlen(key) + 1];
	this->key[0] = '\0';
	strcat(this->key, key);

	this->val = new char[strlen(val) + 1];
	this->val[0] = '\0';
	strcat(this->val, val);
}

HtmlStyleAttribute::HtmlStyleAttribute(char *key, int val)
{
	this->key = new char[strlen(key) + 1];
	this->key[0] = '\0';
	strcat(this->key, key);
	this->val = new char[10];
	sprintf(this->val, "%d", val);
}

HtmlStyleAttribute::HtmlStyleAttribute(char *key, float val){
	this->key = new char[strlen(key) + 1];
	this->key[0] = '\0';

	this->val = new char[15];
	dtostrf(val, 4, 2, this->val);
}

HtmlStyleAttribute::~HtmlStyleAttribute(){
	delete[] key;
	delete[] val;
}

void HtmlStyleAttributeArray::print(char *text)
{
	HtmlStyleAttribute *current = (HtmlStyleAttribute *)this->getFirst();
	do
	{
		if (current != nullptr)
		{
			((HtmlTagAccess *)current)->print(text);
		}
	} while ((current = (HtmlStyleAttribute *)this->getNext(current)) != nullptr);
}

void HtmlStyleAttributeArray::append(char *key, char *value){
	HtmlStyleAttribute *attribute = new HtmlStyleAttribute(key, value);
	XmlArray::append(attribute);
}

void HtmlStyleAttributeArray::append(char *key,  int value){
	HtmlStyleAttribute *attribute = new HtmlStyleAttribute(key, value);
	XmlArray::append(attribute);
}

void HtmlStyleAttributeArray::append(char *key,  float value){
	HtmlStyleAttribute *attribute = new HtmlStyleAttribute(key, value);
	XmlArray::append(attribute);
}

void HtmlCustomTag::print(char *text)
{
	if (style != nullptr)
		getAttributes()->append(ATT_STYLE, style);
	XmlTag::print(text);
}


HtmlCustomTag::HtmlCustomTag(char *tag) : XmlTag(tag){

};

HtmlStyleAttributeArray *HtmlCustomTag::getStyle()
{
	if (style == nullptr)
		style = new HtmlStyleAttributeArray();
	return style;
}

void HtmlInput::print(char *text)
{
	HtmlInputableTag::print(text);
}

void HtmlInputableTag::print(char *text){
	if (this->disabled)
		this->getAttributes()->append(ATT_DISABLED);
	HtmlCustomTag::print(text);
}

HtmlInput::HtmlInput() : HtmlInputableTag(TAG_INPUT)
{

};

void HtmlInputableTag::setName(char *name)
{
	getAttributes()->append(TAG_NAME, name);
}

char *HtmlInputableTag::getName()
{
	return getAttributes()->getStringValueByKey(TAG_NAME);
}

char *HtmlInputableTag::getId()
{
	return getAttributes()->getStringValueByKey(TAG_ID);
}

void HtmlInputableTag::setId(char *id)
{
	getAttributes()->append(TAG_ID, id);
}

HtmlInputableTag::HtmlInputableTag(char *id) : HtmlCustomTag(id)
{
	;
};

int HtmlInputableTag::getSize()
{
	return size;
}

void HtmlInputableTag::setSize(int size)
{
	this->size = size;
}

void HtmlInputableTag::setDisabled(bool state)
{
	this->disabled = state;
}

bool HtmlInputableTag::isDisabled()
{
	return this->disabled;
}

void HtmlInput::setValue(char *value)
{
	getAttributes()->append(ATT_VALUE, value);
}

void HtmlInput::setValue(float value)
{
	getAttributes()->append(ATT_VALUE, value);
}

void HtmlInput::setValue(bool value)
{
	if (value)
	{
		getAttributes()->append(ATT_VALUE, "true");
	}
	else
	{
		getAttributes()->append(ATT_VALUE, "false");
	}
}

void HtmlInput::setValue(int value)
{
	getAttributes()->append(ATT_VALUE, value);
}

HtmlPassword::HtmlPassword() : HtmlInput()
{
	getAttributes()->append(ATT_TYPE, ATT_PASSWORD);
};

HtmlText::HtmlText() : HtmlInput()
{
	getAttributes()->append(ATT_TYPE, ATT_TEXT);
};

void HtmlNumber::print(char *text)
{
	this->getAttributes()->append(ATT_MAX, max);
	this->getAttributes()->append(ATT_MIN, min);
	this->getAttributes()->append(ATT_STEP, (float)step);
	HtmlInput::print(text);
}

HtmlNumber::HtmlNumber() : HtmlInput()
{
	getAttributes()->append(ATT_TYPE, ATT_NUMBER);
};

void HtmlNumber::setMax(int max)
{
	this->max = max;
}

int HtmlNumber::getMax()
{
	return max;
}

void HtmlNumber::setMin(int min)
{
	this->min = min;
}

int HtmlNumber::getMin()
{
	return this->min;
}

void HtmlNumber::setStep(float step)
{
	this->step = step;
}

HtmlHidden::HtmlHidden() : HtmlInput()
{
	getAttributes()->append(ATT_TYPE, ATT_HIDDEN);
};

void HtmlCheckBox::print(char *text)
{
	HtmlHidden *hidden = new HtmlHidden();
	hidden->setId(this->getId());
	hidden->setName(this->getName());
	hidden->setValue(false);
	
	((HtmlTagAccess *)hidden)->print(text);
	char buf[180];
	sprintf(buf, "%s_1", this->getId());
	this->setId(buf);
	buf[0] = '\0';
	sprintf(buf, "document.getElementById('%s').disabled = document.getElementById('%s').checked;", hidden->getId(), this->getId());
	getAttributes()->append("onClick", buf);
	getAttributes()->append(ATT_VALUE, "true");
	if (state)
		getAttributes()->append(ATT_CHECKED);
	delete hidden;

	HtmlInput::print(text);
}

HtmlCheckBox::HtmlCheckBox() : HtmlInput()
{
	getAttributes()->append(ATT_TYPE, ATT_CHECKBOX);
};

void HtmlCheckBox::setValue(bool value)
{
	state = value;
}

void HtmlOption::print(char *text)
{
	if (selected)
		getAttributes()->append(ATT_SELECTED);
	HtmlCustomTag::print(text);
}

HtmlOption::HtmlOption() : HtmlCustomTag(ATT_OPTION) {}

void HtmlOption::setKey(char *key)
{
	this->getAttributes()->append(ATT_VALUE, key);
}

void HtmlOption::setKey(int key)
{
	this->getAttributes()->append(ATT_VALUE, key);
}

int HtmlOption::getKeyInt()
{
	return this->getAttributes()->getIntValueByKey(ATT_VALUE);
}

char *HtmlOption::getKey()
{
	return this->getAttributes()->getStringValueByKey(ATT_VALUE);
}

bool HtmlOption::getSelected()
{
	return selected;
}

void HtmlOption::setSelected(bool selected)
{
	this->selected = selected;
}

HtmlComboBox::HtmlComboBox() : HtmlInputableTag(ATT_SELECT)
{

}

void HtmlComboBox::append(char *key, char *value)
{
	HtmlOption *option = new HtmlOption();
	option->getAttributes()->append(ATT_VALUE, key);
	option->setText(value);
	XmlArray::append(option);
}


void HtmlComboBox::append(const char *key, const char *value)
{
	this->append((char*)key, (char*)value);
}

void HtmlComboBox::append(int key, char *value)
{  
	char buf[10];
	sprintf(buf, "%d", key);
	append(buf, value);
}

void HtmlComboBox::append(int key, const char *value)
{  
	this->append(key, (char*) value);
}

void HtmlComboBox::setSelected(int key){
	char buf[10];
	sprintf(buf, "%d", key);
	setSelected(buf);
}

void HtmlComboBox::setSelected(char *key)
{
	HtmlOption *current = (HtmlOption *)HtmlCustomTag::getFirst();
	do
	{
		if (current != nullptr)
		{
			if (strcmp(current->getKey(), key) == 0)
			{
				current->setSelected(true);
				break;
			}
		}
	} while ((current = (HtmlOption *)this->getNext(current)) != nullptr);
}

void HtmlComboBox::setSelected(const char *key){
	this->setSelected((char*) key);
}

void HtmlHeader::print(char *text)
{
	if ((style != nullptr) && (!this->hasObject(style)))
		this->insert(style, ipFirst);
	if ((title != nullptr) && (!this->hasObject(title)))
		this->insert(title, ipFirst);
	XmlTag::print(text);
}

HtmlStyle *HtmlHeader::getStyle(){
	if (style == nullptr)
		style = new HtmlStyle();
	return style; 
}

HtmlHeader::HtmlHeader(char *name) : XmlTag(name){};

void HtmlHeader::setTitle(char *title)
{
	if (this->title == nullptr)
		this->title = new HtmlCustomTag(TAG_TITLE);
	this->title->setText(title);
}


void HtmlHeader::append(IPrintableObject *val){
	XmlArray::append(val);
}

HtmlPage::HtmlPage() : XmlTag(PAGE_BODY){};

HtmlPage::~HtmlPage()
{
	if (header != nullptr)
		delete header;
	
	if (footer != nullptr)
		delete footer;
}

HtmlHeader *HtmlPage::getHeader()
{
	if (header == nullptr)
		header = new HtmlHeader(PAGE_HEADER);
	return header;
}

HtmlTag *HtmlPage::getFooter()
{
	if (footer == nullptr)
		footer = new HtmlTag(PAGE_FOOTER);
	return footer;
}

void HtmlPage::print(char *text)
{
	strcat(text, "<html>");
	if (header != nullptr)
		((HtmlTagAccess *)header)->print(text);
	XmlTag::print(text);
	if (footer != nullptr)
		((HtmlTagAccess *)footer)->print(text);
	strcat(text, "</html>");
}

void HtmlPage::append(IPrintableObject *val){
	XmlArray::append(val);
}

void HtmlCols::print(char *text)
{
	IPrintableObject *current = getFirst();
	do
	{
		if ((current != nullptr) && (!((XmlArray *)current)->isEmpty()))
		{
			((HtmlTagAccess *)current)->print(text);
		}
	} while ((current = this->getNext(current)) != nullptr);
}

void HtmlCols::append(IPrintableObject *val){
	XmlArray::append(val);
}

void HtmlRow::print(char *text)
{
	setText((IPrintableObject *)cols);
	XmlTag::print(text);
}

HtmlRow::HtmlRow(int col) : HtmlCustomTag(TAG_TR)
{
	cols = new HtmlCols();
	for (int i = 0; i < col; i++)
		cols->append(new HtmlTag(TAG_TD));
}

HtmlCustomTag *HtmlRow::getCol(int i)
{
	return (HtmlCustomTag *)cols->get(i);
}

void HtmlTable::print(char *text)
{
	setText((IPrintableObject *)rows);
	HtmlCustomTag::print(text);
}

HtmlTable::HtmlTable(int cols) : HtmlCustomTag(TAG_TABLE)
{
	rows = new HtmlRows();
	this->cols = cols;
}

int HtmlTable::append()
{
	return rows->append(new HtmlRow(cols));
}

void HtmlTable::append(int rows)
{
	for (int i = 0; i < rows; i++)
		this->append();
}

void HtmlTable::setCell(int row, int col, IPrintableObject *value)
{
	((HtmlRow *)rows->get(row))->getCol(col)->setText(value);
}

void HtmlTable::setCell(int row, int col, double value)
{
	((HtmlRow *)rows->get(row))->getCol(col)->setText(value);
}

void HtmlTable::setCell(int row, int col, int value)
{
	((HtmlRow *)rows->get(row))->getCol(col)->setText(value);
}

void HtmlTable::setCell(int row, int col, float value)
{
	((HtmlRow *)rows->get(row))->getCol(col)->setText(value);
}

void HtmlTable::setCell(int row, int col, const char *value)
{
	((HtmlRow *)rows->get(row))->getCol(col)->setText(value);
}

HtmlStyleAttributeArray *HtmlTable::getCellStyle(int row, int col)
{
	return ((HtmlRow *)rows->get(row))->getCol(col)->getStyle();
}

XmlAttributes *HtmlTable::getCellAttribute(int row, int col)
{
	return ((HtmlRow *)rows->get(row))->getCol(col)->getAttributes();
}

HtmlStyleAttributeArray *HtmlTable::getRowStyle(int row)
{
	return ((HtmlRow *)rows->get(row))->getStyle();
}

HtmlForm::HtmlForm(char *id, char* url, HtmlFormMethod method) : HtmlTag(TAG_FORM)
{
	getAttributes()->append(TAG_ID, id);
	getAttributes()->append(ATT_ACTION, url);
	if (method == Get)
	{
		getAttributes()->append(ATT_METHOD, ATT_GET_METHOD);
	}
	else
	{
		getAttributes()->append(ATT_METHOD, ATT_POST_METHOD);
	}
}

HtmlLink::HtmlLink(char *link, char *caption) : HtmlCustomTag(TAG_A)
{
	this->getAttributes()->append(ATT_HREF, link);
	this->setText(caption);
}

HtmlLink::HtmlLink(char *link) : HtmlCustomTag(TAG_A)
{
	this->getAttributes()->append(ATT_HREF, link);
	this->setText(link);
}

HtmlStyleGroup::HtmlStyleGroup(char *tag){
	this->tag = new char[strlen(tag) + 1];
	this->tag[0] = '\0';
	strcat(this->tag, tag);
}

HtmlStyleGroup::~HtmlStyleGroup(){
	delete[] tag;
}

void HtmlStyleGroup::print(char *text){
	strcat(text, tag);
	strcat(text, " {");
	HtmlStyleAttributeArray *current = (HtmlStyleAttributeArray *)this->getFirst();
	do
	{
		if (current != nullptr)
		{
			((HtmlTagAccess *)current)->print(text);
		}
	} while ((current = (HtmlStyleAttributeArray *)this->getNext(current)) != nullptr);
	strcat(text, "} ");
}

HtmlStyleGroup* HtmlStyle::createGroup(char *tag){
	HtmlStyleGroup* group = new HtmlStyleGroup(tag);
	append(group);
	return group;
}

HtmlStyle::HtmlStyle() : XmlTag(TAG_STYLE){
	;
}

HtmlButton::HtmlButton(char *caption, char *formId) : HtmlCustomTag(TAG_BUTTON){
	setText(caption);
	this->getAttributes()->append(TAG_FORM, formId);
}

HtmlButton::HtmlButton(char *caption): HtmlCustomTag(TAG_BUTTON){
	setText(caption);
}


HtmlTag::HtmlTag(char *tag): HtmlCustomTag(tag){
	;
}

void HtmlTag::append(IPrintableObject *val){
	XmlArray::append(val);
}

int HtmlRows::append(IPrintableObject *val){
	return XmlArray::append(val);
}	