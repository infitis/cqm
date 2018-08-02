//---------------------------------------------------------------------------
#include "cqmcore.h"
#include "cqmio.h"
#include "ioclass.h"
#include "pcl836.h"
#include "signals.h"

//---------------------------------------------------------------------------
Device_pcl836::Device_pcl836(void) : Device()
{
	strcpy(model, "Advantech PCL-836");
	strcpy(name, "noname");
    ioclass = DEVICE_PCL836;
    base = irq = dma = 0;

}


//---------------------------------------------------------------------------
Device_pcl836_counters::Device_pcl836_counters(void) : Device_pcl836()
{
    ioclass = DEVICE_PCL836_COUNTERS_IN;
}

//---------------------------------------------------------------------------
void Device_pcl836_counters::Start(void)
{
    Device::Start();
    /*
    TODO: сделать проверку наличия устройства
    */

	set_counter_clock_input_mode(0,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	set_counter_clock_input_mode(1,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	set_counter_clock_input_mode(2,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	set_counter_clock_input_mode(3,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	set_counter_clock_input_mode(4,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	set_counter_clock_input_mode(5,CCR_EXTRENAL_CLOCK_WITHOUT_FILTER | CCR_POSITIVE_EDGE);
	//init max value counter 0
	Put(0, 0, MAX_COUNTER_VALUE);
	//init max value counter 1
	Put(1, 1, MAX_COUNTER_VALUE);
	//init max value counter 2
	Put(2, 2, MAX_COUNTER_VALUE);
	//init max value counter 0
	Put(3, 0, MAX_COUNTER_VALUE);
	//init max value counter 1
	Put(4, 1, MAX_COUNTER_VALUE);
	//init max value counter 2
	Put(5, 2, MAX_COUNTER_VALUE);
}

//---------------------------------------------------------------------------
void Device_pcl836_counters::Stop(void)
{

}

//---------------------------------------------------------------------------
int Device_pcl836_counters::Get(int offset, int bit)
{
	int select=0;
    switch(bit)
    {
    	case 0 : {select=SELECT_COUNTER_0;break;}
        case 1 : {select=SELECT_COUNTER_1;break;}
        case 2 : {select=SELECT_COUNTER_2;break;}
    }
	write_counter_control_word(offset,
                                 select
                               | RW_LSB_MSB
                               | MODE_1
                               | BCD_16_BIT);


	int chip = 0;
   	if (offset >= 3) chip = 1;
   	unsigned short low = PortReadByte(base+8+offset+chip);
    unsigned short hi  = PortReadByte(base+8+offset+chip);

	Put(offset, bit, MAX_COUNTER_VALUE);

    return low + (hi << 8);
}

//---------------------------------------------------------------------------
int Device_pcl836_counters::Put(int offset, int bit, int data)
{
	int select=0;
    switch(bit)
    {
    	case 0 : {select=SELECT_COUNTER_0;break;}
        case 1 : {select=SELECT_COUNTER_1;break;}
        case 2 : {select=SELECT_COUNTER_2;break;}
    }
    write_counter_control_word(offset,
                                 select
                               | RW_LSB_MSB
                               | MODE_1
                               | BCD_16_BIT);

    int chip = 0;
    if (offset >= 3) chip = 1;
    PortWriteByte(base+8+offset+chip, data);
    PortWriteByte(base+8+offset+chip, data >> 8);
    return 0;
}

//---------------------------------------------------------------------------
void Device_pcl836_counters::set_counter_clock_input_mode(int counter, unsigned char mode)
{
    PortWriteByte(base+18+counter, mode);
}

//---------------------------------------------------------------------------
void Device_pcl836_counters::write_counter_control_word(int counter, unsigned char cw)
{
    int chip = 0;
    if (counter >= 3) chip = 1;
    PortWriteByte(base+11+chip*4, cw);
}

//---------------------------------------------------------------------------
void Device_pcl836_counters::write_fout_control_word(int fout, unsigned char cw)
{
    int chip = 0;
    if (fout >= 3) chip = 1;
    PortWriteByte(base+3+chip*4, cw);
    return;
}




//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Device_pcl836_discrete::Device_pcl836_discrete(void) : Device_pcl836()
{
    ioclass = DEVICE_PCL836_DISCRETE_IN;
}

//---------------------------------------------------------------------------
int Device_pcl836_discrete::Get(int offset, int bit)
{
	//Устанавливаем нужный канал
    Put(16, 0, offset| WR_RD_836);
	//Мультиплексор коммутирует
    //и мы считываем нужный байт
	unsigned char ret = PortReadByte(base+16);
    ret = ret << (7 - bit);
    ret = ret >> 7;
	return ret;
}

//---------------------------------------------------------------------------
int Device_pcl836_discrete::Put(int offset, int bit, int data)
{
	PortWriteByte(base+offset,data);
    return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FreqSignal836::FreqSignal836(void) : FreqSignal()
{
	strcpy(name,"some_freq_signal_836");
    type = SIGNAL_FREQ_836;
    prev = -1;
    devotion = -1;
}

//---------------------------------------------------------------------------
void FreqSignal836::In (void)
{
	if (!active) data = defaultvalue;
    else
    {
        prev = devotion;
		devotion = dev->Get(offset, bit);
        if (prev == -1)
        {
            prev = devotion;
            data = defaultvalue;
        }
        else
        {
            data = prev - devotion;
            if (data < 0)
            {
                data += MAX_COUNTER_VALUE;
            }
            data = (int)(data / (core.io->tick1 / 1000.0));
        }
    }
}

//---------------------------------------------------------------------------
char* FreqSignal836::format(void)
{
    if (core.vi("debug") & CORE_DEBUG_HARDWARE)
    {
        sprintf(str, "%4i(%4i-%4i)", data, prev, devotion);
        return str;
    }
    return Signal::format();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

