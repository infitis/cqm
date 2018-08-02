select * from pack_point('p20', -45, -30);
select * from pack_point('p4',  -30, -15);
select * from pack_point('p5',  -30, -15);
DELETE FROM POINTS WHERE POINT='p4' AND MOMENT < addday(CURRENT_DATE, -120);
DELETE FROM POINTS WHERE POINT='p5' AND MOMENT < addday(CURRENT_DATE, -120);

