//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "ioclass.h"
#include "cqmio.h"
#include "signals.h"
#include "device.h"

//---------------------------------------------------------------------------
Signal::Signal(void)
{
	strcpy(name,"some_signal");
    type = SIGNAL_NONE;
    strcpy(devname, "no_device");
    dev = 0;
    method = offset = bit = inverse = active = defaultvalue = data = result = 0;
}

//---------------------------------------------------------------------------
void Signal::Init(const char* name_, int type_, const char* devname_,
                  int offset_, int bit_, int inverse_, int active_, int defaultvalue_)
{
	strcpy(name, name_);
    type =		type_;
    strcpy(devname, devname_);
    offset =	offset_;
    bit =		bit_;
    inverse =	inverse_;
	active =    active_;
    defaultvalue = defaultvalue_;
}

//---------------------------------------------------------------------------
void Signal::FindDevice(Device** devs, int devscount)
{
    for (int i=0; i<devscount; i++)
    {
    	if (!strcmp(devname, devs[i]->name))
        {
        	dev = devs[i];
            return;
        }
    }

	//Нет такого устройства
	char msg[MAX_NAME_LEN] = "Can not find device for signal ";
	throw logic_error(strcat(msg, name));
}

//---------------------------------------------------------------------------
char* Signal::format(void)
{
    char t[8];
    sprintf(t, "%%%ii", flen);
    sprintf(str, t, data);
    return str;
}

//---------------------------------------------------------------------------
void Signal::Out(void)
{
	dev->Put(offset, bit, data);
}

//---------------------------------------------------------------------------
void Signal::In (void)
{
	if (!active) data = defaultvalue;
    else data = dev->Get(offset, bit);
}

//---------------------------------------------------------------------------
istream& Signal::Input(istream& s)
{
	s>>method>>name>>title>>
              devname>>offset>>bit>>inverse>>active>>defaultvalue;
    flen = strlen(name);
    return s;
}

//---------------------------------------------------------------------------
ostream& Signal::Print(ostream& s)
{
	return s<<type<<"\t"<<method<<"\t"<<name<<"\t"<<title
            <<"\t"<<devname
    		<<"\t"<<offset<<"\t"<<bit<<"\t"<<inverse
            <<"\t"<<active<<"\t"<<defaultvalue;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, Signal& d)
{
	return d.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, Signal& d)
{
    return d.Input(s);
}



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DiscreteSignal::DiscreteSignal(void) : Signal()
{
	strcpy(name,"some_discrete_signal");
    type = SIGNAL_DISCRETE;
}

//---------------------------------------------------------------------------
void DiscreteSignal::Out(void)
{
	dev->Put(offset, bit, data);
}

//---------------------------------------------------------------------------
void DiscreteSignal::In (void)
{
	Signal::In();
    if (inverse && active)
    	data = data ? 0 : 1;
}

//---------------------------------------------------------------------------
char* DiscreteSignal::format(void)
{
    return Signal::format();
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FreqSignal::FreqSignal(void) : Signal()
{
	strcpy(name,"some_freq_signal");
    type = SIGNAL_FREQ;
}

//---------------------------------------------------------------------------
void FreqSignal::Out(void)
{
	dev->Put(offset, bit, data);
}

//---------------------------------------------------------------------------
void FreqSignal::In (void)
{
	if (!active) data = defaultvalue;
    else data = dev->Get(offset, bit);
}

//---------------------------------------------------------------------------
char* FreqSignal::format(void)
{
    return Signal::format();
}



//---------------------------------------------------------------------------
#pragma package(smart_init)
