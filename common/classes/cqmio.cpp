//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmio.h"
#include "cqmstreamparse.h"
#include "device.h"
#include "signals.h"
#include "pcl836.h"
#include "dev_a10.h"

//---------------------------------------------------------------------------
HardwareIO::HardwareIO(void)
{
    DeviceCount = 0;
    SignalCount = 0;
    tick1 = tick2 = tick3 = 0;
}

//---------------------------------------------------------------------------
HardwareIO::~HardwareIO(void)
{
}

//---------------------------------------------------------------------------
void HardwareIO::LoadIO(const char* filename)
{
	//открыть файл
    f.open(filename);

    if (!f/*.is_open()*/)
    {
		char msg[MAX_NAME_LEN] = "Can`t open file ";
		throw logic_error(strcat(msg, filename));
    }
    while (!f.eof())
    {
        //найти раздел (signals или devices)
        //загрузить данные из раздела
        //найти другой раздел

    	char str[MAX_NAME_LEN];

        SkipSpacesAndComments(f);

        f>>str;

        if (!strcmp(str, "start"))
			f>>name;
        else
        if (!strcmp(str, "devices"))
			LoadDevices();
        else
        if (!strcmp(str, "signals"))
			LoadSignals();
        else

        if (!strcmp(str, "end"))
			break;
    }
    //закрыть файл
    f.close();
    //проверка как прошла загрузка
}

//---------------------------------------------------------------------------
void HardwareIO::ClearIO(void)
{
	//очистим сигналы
	for (int i=0; i<SignalCount; i++)
	{
		delete signals[i];
    }

    //очистим устройства
	for (int i=0; i<DeviceCount; i++)
	{
		delete devices[i];
    }
}



//---------------------------------------------------------------------------
void HardwareIO::StartIO(void)
{
	//запустим каждое устройство
	for (int i=0; i<DeviceCount; i++)
	{
		devices[i]->Start(/*this*/);
    }

	//Найдем для каждого сигнала своё устройство
	for (int i=0; i<SignalCount; i++)
	{
		signals[i]->FindDevice(devices, DeviceCount);
    }
}

//---------------------------------------------------------------------------
void HardwareIO::StopIO (void)
{
	//Остановим каждое устройство
	for (int i=0; i<DeviceCount; i++)
	{
		devices[i]->Stop();
    }

}

//---------------------------------------------------------------------------
int HardwareIO::LoadDevices(void)
{
	//временные переменные для считывания из потока
    char n[MAX_NAME_LEN];
    int ioc;

    Device * d;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
			(f)>>ioc;
			if (f.eof())
            {
            	char msg[MAX_NAME_LEN] = "LoadDevices: a few params for device";
				throw logic_error(msg);
                //return 1;
            }
			switch (ioc)
			{
				case DEVICE_UNKNOWN:
                {
					d = new Device();
					break;
                }
				case DEVICE_PCL836:
                {
                    d = new Device_pcl836();
                    break;
                }
				case DEVICE_PCL836_DISCRETE_IN:
                {
                    d = new Device_pcl836_discrete();
                    break;
                }
				case DEVICE_PCL836_COUNTERS_IN:
                {
                    d = new Device_pcl836_counters();
					break;
                }
				case DEVICE_A10_DISCRETE_IN:
                {
                    d = new Device_a10_discrete();
                    break;
                }
				case DEVICE_A10_COUNTERS_IN:
                {
                    d = new Device_a10_counters();
					break;
                }
				default:
                {
    	        	char msg[MAX_NAME_LEN] = "LoadDevices: unknown ioclass";
					throw logic_error(msg);
        	        //return 1;
                }
        	}
            f>>(*d);
            if (DeviceCount < MAX_DEVICES-1)
            {
                devices[DeviceCount++] = d;
            }
            else
            {
                delete d;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int HardwareIO::LoadSignals(void)
{
	//временные переменные для считывания из потока
    char n[MAX_NAME_LEN];
    int type;

    Signal * s;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		f>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
			f>>type;
			if (f.eof())
            {
            	char msg[MAX_NAME_LEN] = "LoadSignals: a few params for signals";
				throw logic_error(msg);
                //return 1;
            }
            int masked_type = (~SIGNAL_MASK) & type;
			switch (masked_type)
			{
				case SIGNAL_NONE:
                {
					s = new Signal();
					break;
                }
				case SIGNAL_DISCRETE:
                {
                    s = new DiscreteSignal();
                    break;
                }
				case SIGNAL_FREQ:
                {
                    s = new FreqSignal();
                    break;
                }
				case SIGNAL_FREQ_836:
                {
                    s = new FreqSignal836();
                    break;
                }
				case SIGNAL_FREQ_A10:
                {
                    s = new FreqSignal_a10();
                    break;
                }
				default:
                {
    	        	char msg[MAX_NAME_LEN] = "LoadSignals: unknown type";
					throw logic_error(msg);
        	        //return 1;
                }
        	}
            f>>(*s);
            s->type = type;
            if (SignalCount < MAX_SIGNALS-1)
            {
                signals[SignalCount++] = s;
            }
            else
            {
                delete s;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
void HardwareIO::ReadAllSignals(void)
{
	for (int i=0; i<SignalCount; i++)
	{
		signals[i]->In();
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

