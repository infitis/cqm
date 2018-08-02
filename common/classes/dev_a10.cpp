//---------------------------------------------------------------------------
#include "cqmcore.h"
#include "cqmio.h"
#include "dev_a10.h"
#include "ioclass.h"

//---------------------------------------------------------------------------
Device_a10_counters::Device_a10_counters(void) : Device()
{
    ioclass = DEVICE_A10_COUNTERS_IN;
}

//---------------------------------------------------------------------------
void Device_a10_counters::Start(void)
{
    Device::Start();
    /*
    TODO: сделать проверку наличия устройства
    */
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
void Device_a10_counters::Stop(void)
{

}

//---------------------------------------------------------------------------
int Device_a10_counters::Get(int offset, int bit)
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


	int chip;
    int os;//local offset
   	if (offset >= 3) {chip = 1; os = offset-3;}
    else             {chip = 0; os = offset;  }
   	unsigned short low = PortReadByte(base+12+chip*4+os);
    unsigned short hi  = PortReadByte(base+12+chip*4+os);

	Put(offset, bit, MAX_COUNTER_VALUE);

    return low + (hi << 8);
}

//---------------------------------------------------------------------------
int Device_a10_counters::Put(int offset, int bit, int data)
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

	int chip;
    int os;//local offset
   	if (offset >= 3) {chip = 1; os = offset-3;}
    else             {chip = 0; os = offset;  }
    PortWriteByte(base+0+chip*4+os, data);
    PortWriteByte(base+0+chip*4+os, data >> 8);
    return 0;
}

//---------------------------------------------------------------------------
void Device_a10_counters::write_counter_control_word(int counter, unsigned char cw)
{
    int chip = 0;
    if (counter >= 3) chip = 1;
    PortWriteByte(base+0+chip*4+3, cw);
}

//---------------------------------------------------------------------------
Device_a10_discrete::Device_a10_discrete(void) : Device()
{
    ioclass = DEVICE_A10_DISCRETE_IN;
}

//---------------------------------------------------------------------------
int Device_a10_discrete::Get(int offset, int bit)
{
	//Устанавливаем нужный канал
    Put(24, 0, offset| WR_RD_A10);
	//Мультиплексор коммутирует
    //и мы считываем нужный байт
	unsigned char ret = PortReadByte(base+28);
    ret = ret << (7 - bit);
    ret = ret >> 7;
	return ret;
}

//---------------------------------------------------------------------------
int Device_a10_discrete::Put(int offset, int bit, int data)
{
	PortWriteByte(base+offset,data);
    return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FreqSignal_a10::FreqSignal_a10(void) : FreqSignal()
{
	strcpy(name,"some_freq_signal_a10");
    type = SIGNAL_FREQ_A10;
    prev = -1;
    devotion = -1;
}

//---------------------------------------------------------------------------
void FreqSignal_a10::In (void)
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
char* FreqSignal_a10::format(void)
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

