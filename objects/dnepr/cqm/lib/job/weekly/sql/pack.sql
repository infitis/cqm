select * from pack_point('p516',  -45, -30);
select * from pack_point('p502',  -45, -30);
select * from pack_point('p515',  -45, -30);

select * from pack_route('lift',  -45, -30);

-- DELETE FROM POINTS WHERE POINT='p516' AND MOMENT < addday(CURRENT_DATE, -60);
-- DELETE FROM POINTS WHERE POINT='p502' AND MOMENT < addday(CURRENT_DATE, -60);
-- DELETE FROM POINTS WHERE POINT='p515' AND MOMENT < addday(CURRENT_DATE, -60);

