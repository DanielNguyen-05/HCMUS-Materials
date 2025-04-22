--Q27. Cho biết số lượng giáo viên và tổng lương của họ.
select count(MAGV) as SOLUONGGIAOVIEN, sum(LUONG) as TONGLUONG
from GIAOVIEN

--Q28. Cho biết số lượng giáo viên và lương trung bình của từng bộ môn.
select MABM, count(MAGV) as SOLUONGGIAOVIEN, avg(LUONG) as LUONGTRUNGBINH
from GIAOVIEN
group by GIAOVIEN.MABM

--Q29. Cho biết tên chủ đề và số lượng đề tài thuộc về chủ đề đó.
select cd.MaCD, cd.TENCD as TENCHUDE, count(dt.MADT) as SOLUONGDETAI
from CHUDE cd
left join DETAI dt on dt.MACD = cd.MACD
group by cd.MaCD, cd.TENCD 

--Q30. Cho biết tên giáo viên và số lượng đề tài mà giáo viên đó tham gia.
select gv.MAGV, gv.HOTEN as TENGIAOVIEN, count(tgdt.MADT) as SOLUONGDETAITHAMGIA
from GIAOVIEN gv
left join THAMGIADT tgdt on gv.MAGV = tgdt.MAGV
group by gv.MAGV, gv.HOTEN

--Q31. Cho biết tên giáo viên và số lượng đề tài mà giáo viên đó làm chủ nhiệm.
select gv.MAGV, gv.HOTEN as TENGIAOVIEN, count(dt.MADT) as SOLUONGDETAICHUNHIEM
from GIAOVIEN gv
left join DETAI dt on gv.MAGV = dt.GVCNDT
group by gv.MAGV, gv.HOTEN

--Q32. Với mỗi giáo viên cho tên giáo viên và số người thân của giáo viên đó.
select gv.MAGV, gv.HOTEN as TENGIAOVIEN, count(nt.MAGV) as SOLUONGNGUOITHAN
from GIAOVIEN gv
left join NGUOITHAN nt on gv.MAGV = nt.MAGV
group by gv.MAGV, gv.HOTEN

--Q33. Cho biết tên những giáo viên đã tham gia từ 3 đề tài trở lên.
select gv.MAGV, gv.HOTEN as TENGIAOVIEN
from GIAOVIEN gv
join THAMGIADT tgdt on tgdt.MAGV = gv.MAGV
group by gv.MAGV, gv.HOTEN having count(tgdt.MADT) >= 3

--Q34. Cho biết số lượng giáo viên đã tham gia vào đề tài Ứng dụng hóa học xanh.
select count(tgdt.MAGV) as SOLUONGGIAOVIEN
from THAMGIADT tgdt 
join DETAI dt on dt.MADT = tgdt.MADT
where dt.TENDT = N'Ứng dụng hóa học xanh'
