<?php
/*
class CoalHeap for cqm scripts
Copyright (c) Ruslan Keba 2004
*/

define("P_MIN", 0.1);
define("N_MIN", 0.1);
define("A_MIN", 2.0);
define("A_MAX", 80.0);
define("H_MIN", 2.0);
define("H_MAX", 80.0);

class Coal    //уголь
{
    function Coal($p=0, $a=0, $h=0)//конструктор
    {
        $this->P = $p;        
        $this->A = $a;        
        $this->H = $h;        
    }
    
    function cempty()//true если p=a=h=0;
    {
        if ($this->P == 0 && $this->A == 0 && $this->H == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    function setempty()//set p=a=h=0;
    {
        $this->P = 0;
        $this->A = 0;
        $this->H = 0;
    }

    var $P;//вес угля
    var $A;//зольность угля
    var $H;//влажность угля

    function format()
    {
        return "[".$this->P.",".$this->A.",".$this->c->H."]";
    }
}

class CoalHeap
{
    var $c;  //уголь
    var $n;  //количесво циклов за который добавляли или отнимали уголь
    var $dn;
    var $empty; //пустота кучи

    function CoalHeap()
    {
        $this->c = new Coal;
        $this->setEmpty();
        $this->resetDeltaN();
    }

    function addCoal ($m)//добавить угля
    {
        if ($m->cempty())
            return;

        $this->addAsh($m);
        $this->addHum($m);
        $this->addWei($m);
        $this->n += $dn;
        $this->correctCoal();
        $this->resetDeltaN();
    }

    function subCoal ($m)//отнять угля
    {
        if ($m->cempty())
            return;

        $this->subAsh($m);
        $this->subHum($m);
        $this->subWei($m);
        $this->$n -= $dn;
        $this->correctCoal();
        $this->resetDeltaN();
    }

    function addAsh($m)
    {
        if (is_null($m->A) || $m->A<=A_MIN)
            return;

        if (is_null($this->c->A) || $this->c->A<=A_MIN)
            $this->c->A = $m->A;

        if (!is_null($this->c->P) && !is_null($m->P) && ($this->c->P + $m->P)>=P_MIN)
        {
             $this->c->A = ($this->c->A * $this->c->P + $m->A * $m->P)/($this->c->P + $m->P);
             return;
        }

        $this->c->A = ($this->c->A * $this->n + $m->A->val * $this->dn)/($this->n + $this->dn);
    }

    function addHum($m)
    {
        if (is_null($m->H) || $m->H<=H_MIN)
            return;

        if (is_null($this->c->H) || $this->c->H<=H_MIN)
            $this->c->H = $m->H;

        if (!is_null($this->c->P) && !is_null($m->P) && ($this->c->P + $m->P)>=P_MIN)
        {
             $this->c->H = ($this->c->H * $this->c->P + $m->H * $m->P)/($this->c->P + $m->P);
             return;
        }

        $this->c->H = ($this->c->H * $this->n + $m->H->val * $this->dn)/($this->n + $this->dn);
    }

    function addWei($m)
    {
        if (is_null($m->P) || $m->P<=P_MIN)
            return;

        if (is_null($this->c->P))
            return;

        $this->c->P += $m->P;
    }

    function subAsh($m)
    {
        if (is_null($m->A) || $m->A<=A_MIN)
            return;

        if (is_null($this->c->A) || $this->c->A<=A_MIN)
            $this->c->A = $m->A;

        if (!is_null($this->c->P) && !is_null($m->P) && ($this->c->P - $m->P)>=P_MIN)
        {
             $this->c->A = ($this->c->A * $this->c->P - $m->A * $m->P)/($this->c->P - $m->P);
             return;
        }

        if ($this->n - $this->dn > N_MIN )
            $this->c->A = ($this->c->A * $this->n - $m->A * $this->dn)/($this->n - $this->dn);
    }

    function subHum($m)
    {
        if (is_null($m->H) || $m->H<=H_MIN)
            return;

        if (is_null($this->c->H) || $this->c->H<=H_MIN)
            $this->c->H = $m->H;

        if (!is_null($this->c->P) && !is_null($m->P) && ($this->c->P - $m->P)>=P_MIN)
        {
             $this->c->H = ($this->c->H * $this->c->P - $m->H * $m->P)/($this->c->P - $m->P);
             return;
        }

        if ($this->n - $this->dn > N_MIN )
            $this->c->H = ($this->c->H * $this->n - $m->H * $this->dn)/($this->n - $this->dn);
    }

    function subWei($m)
    {
        if (is_null($m->P) || $m->P<=P_MIN)
            return;

        if (is_null($this->c->P))
            return;

        $this->c->P -= $m->P;
    }

    function correctCoal()
    {
        if ($this->c->A <= A_MIN || $this->c->A >= A_MAX)
            $this->c->A = NULL;

        if ($this->c->H <= H_MIN || $this->c->H >= H_MAX)
            $this->c->H = NULL;

        if ($this->c->P <= P_MIN)
            $this->setEmpty();
        else
            $this->setNotEmpty();

        if ($this->n <= N_MIN)
            $this->n = 0;
    }

    function setEmpty()//опустошить
    {
        $this->c->setempty();
        $this->n = 0;
        $this->empty = 1;
    }

    function setNotEmpty()//не опустошить
    {
        $this->empty = 0;
    }

    function setDeltaN($dn)//установить dn
    {
        $this->dn = $dn;
        if ($this->dn <= 0)
            $this->resetDeltaN();
    }


    function resetDeltaN()//сбросить dn
    {
        $this->dn = 1.0;
    }

    function format()
    {
        return "(".$this->c->format().",".$this->n.",".$this->empty.")";
    }
}

/* tests */

/*
$ch = new CoalHeap;
$ch->c->P = 10;
$ch->c->A = 30;
print "(".$ch->c->P.",".$ch->c->A.")\n";

$c = new Coal(10, 20, 0);
print "(".$c->P.",".$c->A.")\n";

$ch->addCoal($c);
print "(".$ch->c->P.",".$ch->c->A.")\n";
$ch->subCoal($c);
print "(".$ch->c->P.",".$ch->c->A.")\n";
*/

?>