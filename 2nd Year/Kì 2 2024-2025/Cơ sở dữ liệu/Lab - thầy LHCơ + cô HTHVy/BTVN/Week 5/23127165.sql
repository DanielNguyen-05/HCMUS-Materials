--Q35. Cho biết mức lương cao nhất của các giảng viên.
select distinct LUONG
from GIAOVIEN 
where LUONG >= ALL (select LUONG from GIAOVIEN)

--Q36. Cho biết những giáo viên có lương lớn nhất.
select *
from GIAOVIEN 
where LUONG >= ALL (select LUONG from GIAOVIEN)

--Q37. Cho biết lương cao nhất trong bộ môn “HTTT”.
select distinct gv.LUONG
from GIAOVIEN gv
where gv.MABM = 'HTTT' and gv.LUONG >= ALL (
    select LUONG 
    from GIAOVIEN gv2
    where gv2.MABM = 'HTTT'
)

--Q38. Cho biết tên giáo viên lớn tuổi nhất của bộ môn Hệ thống thông tin.
select gv.HOTEN
from GIAOVIEN gv, BOMON bm
where bm.TenBM = N'Hệ thống thông tin' and bm.MABM = gv.MABM and gv.NGSINH <= ALL (
    select gv2.NGSINH
    from GIAOVIEN gv2, BOMON bm2
    where bm2.TenBM = N'Hệ thống thông tin' and bm2.MABM = gv2.MABM
)

--Q39. Cho biết tên giáo viên nhỏ tuổi nhất khoa Công nghệ thông tin.
select gv.HOTEN
from GIAOVIEN gv
join BOMON bm on bm.MABM = gv.MABM
join KHOA k on k.MAKHOA = bm.MAKHOA
where k.TENKHOA = N'Công nghệ thông tin'
and gv.NGSINH >= ALL (
  select gv2.NGSINH
  from GIAOVIEN gv2
  join BOMON bm2 on bm2.MABM = gv2.MABM
  join KHOA k2 on k2.MAKHOA = bm2.MAKHOA
  where k2.TENKHOA = N'Công nghệ thông tin' 
)

--Q40. Cho biết tên giáo viên và tên khoa của giáo viên có lương cao nhất.
select gv.HOTEN, k.TENKHOA
from GIAOVIEN gv
join BOMON bm on bm.MABM = gv.MABM
join KHOA k on bm.MAKHOA = k.MAKHOA
where gv.LUONG >= ALL (
  select gv2.LUONG
  from GIAOVIEN gv2
  join BOMON bm2 on bm2.MABM = gv2.MABM
  join KHOA k2 on bm2.MAKHOA = k2.MAKHOA
)

--Q41. Cho biết những giáo viên có lương lớn nhất trong bộ môn của họ.
select gv.HOTEN, bm.TenBM, gv.LUONG
from GIAOVIEN gv
join BOMON bm on bm.MABM = gv.MABM
where gv.LUONG >= ALL (
  select gv2.LUONG 
  from GIAOVIEN gv2
  where gv.MABM = gv2.MABM
)

--Q42. Cho biết tên những đề tài mà giáo viên Nguyễn Hoài An chưa tham gia.
select dt.TENDT
from DETAI dt
where not exists (
  select 1
  from THAMGIADT tgdt
  join GIAOVIEN gv on gv.MAGV = tgdt.MAGV
  where tgdt.MADT = dt.MADT and gv.HOTEN = N'Nguyễn Hoài An'
)

--Q43. Cho biết những đề tài mà giáo viên Nguyễn Hoài An chưa tham gia. Xuất ra tên đề tài, tên người chủ nhiệm đề tài.
select dt.TENDT, gv.HOTEN
from DETAI dt
join GIAOVIEN gv on gv.MAGV = dt.GVCNDT
where not exists (
  select 1
  from THAMGIADT tgdt
  join GIAOVIEN gv2 on gv2.MAGV = tgdt.MAGV
  where tgdt.MADT = dt.MADT and gv2.HOTEN = N'Nguyễn Hoài An'
)

--Q44. Cho biết tên những giáo viên khoa Công nghệ thông tin mà chưa tham gia đề tài nào.
select gv.HOTEN
from GIAOVIEN gv
join KHOA k on k.TENKHOA = N'Công nghệ thông tin'
join BOMON bm on bm.MAKHOA = k.MAKHOA
where gv.MABM = bm.MABM and not exists (
  select 1 
  from THAMGIADT tgdt
  where tgdt.MAGV = gv.MAGV
)

--Q45. Tìm những giáo viên không tham gia bất kỳ đề tài nào
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where not exists (
  select 1 
  from THAMGIADT tgdt
  where tgdt.MAGV = gv.MAGV
)

--Q46. Cho biết giáo viên có lương lớn hơn lương của giáo viên “Nguyễn Hoài An”
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where gv.LUONG > (
  select gv2.LUONG
  from GIAOVIEN gv2
  where gv2.HOTEN = N'Nguyễn Hoài An'
)

--Q47. Tìm những trưởng bộ môn tham gia tối thiểu 1 đề tài
select distinct gv.MAGV, gv.HOTEN
from GIAOVIEN gv
join BOMON bm on bm.MABM = gv.MABM
join THAMGIADT tgdt on tgdt.MAGV = gv.MAGV 
where bm.TRUONGBM = gv.MAGV

--Q48. Tìm giáo viên trùng tên và cùng giới tính với giáo viên khác trong cùng bộ môn
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
join GIAOVIEN gv2 on gv.MABM = gv2.MABM and gv.HOTEN = gv2.HOTEN and gv.PHAI = gv2.PHAI
where gv.MAGV != gv2.MAGV

--Q49. Tìm những giáo viên có lương lớn hơn lương của ít nhất một giáo viên bộ môn “Công nghệ phần mềm”
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where gv.LUONG > ANY (
  select gv2.LUONG
  from GIAOVIEN gv2
  join BOMON bm on gv2.MABM = bm.MABM
  where bm.TENBM = N'Công nghệ phần mềm'
)

--Q50. Tìm những giáo viên có lương lớn hơn lương của tất cả giáo viên thuộc bộ môn “Hệ thống thông tin"
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where gv.LUONG >= ALL (
  select gv2.LUONG 
  from GIAOVIEN gv2
  join BOMON bm on bm.MABM = gv2.MABM
  where bm.TENBM = N'Hệ thống thông tin'
)

--Q51. Cho biết tên khoa có đông giáo viên nhất
select k.TENKHOA, COUNT(gv.MAGV) as SoLuongGV
from KHOA k
join BOMON bm on k.MAKHOA = bm.MAKHOA
join GIAOVIEN gv on bm.MABM = gv.MABM
group by k.TENKHOA
having COUNT(gv.MAGV) = (
    select MAX(SoLuongGV)
    from (
        select COUNT(gv2.MAGV) as SoLuongGV
        from KHOA k2
        join BOMON bm2 on k2.MAKHOA = bm2.MAKHOA
        join GIAOVIEN gv2 on bm2.MABM = gv2.MABM
        group by k2.TENKHOA
    ) as SubQuery
)

--Q52. Cho biết họ tên giáo viên chủ nhiệm nhiều đề tài nhất
select gv.HOTEN, count(dt.MADT) as SoLuongDT
from GIAOVIEN gv
join DETAI dt on gv.MAGV = dt.GVCNDT
group by gv.HOTEN
having count(dt.MADT) = (
  select max(SoLuongDT)
  from (
    select count(dt2.MADT) as SoLuongDT
    from GIAOVIEN gv2
    join DETAI dt2 on gv2.MAGV = dt2.GVCNDT
    group by gv2.HOTEN
  ) as SubQuery
)

--Q53. Cho biết mã bộ môn có nhiều giáo viên nhất
select bm.MABM, count(gv.MAGV) as SoLuongGV
from BOMON bm
join GIAOVIEN gv on bm.MABM = gv.MABM
group by bm.MABM
having count(gv.MAGV) = (
  select max(SoLuongGV)
  from (
    select count(gv2.MAGV) as SoLuongGV
    from BOMON bm2
    join GIAOVIEN gv2 on bm2.MABM = gv2.MABM
    group by bm2.MABM
  ) as SubQuery
)

--Q54. Cho biết tên giáo viên và tên bộ môn của giáo viên tham gia nhiều đề tài nhất.
select gv.HOTEN, bm.TENBM, count(tgdt.MADT) as SoLuongDT
from GIAOVIEN gv
join THAMGIADT tgdt on gv.MAGV = tgdt.MAGV
join BOMON bm on gv.MABM = bm.MABM
group by gv.HOTEN, bm.TENBM
having count(tgdt.MADT) = (
  select max(SoLuongDT)
  from (
    select count(tgdt2.MADT) as SoLuongDT
    from GIAOVIEN gv2
    join THAMGIADT tgdt2 on gv2.MAGV = tgdt2.MAGV
    group by gv2.MAGV
  ) as SubQuery
)

--Q55. Cho biết tên giáo viên tham gia nhiều đề tài nhất của bộ môn HTTT.
select gv.HOTEN, count(tgdt.MADT) as SoLuongDT
from GIAOVIEN gv
join THAMGIADT tgdt on gv.MAGV = tgdt.MAGV
join BOMON bm on gv.MABM = bm.MABM
where bm.TENBM = N'Hệ thống thông tin'
group by gv.HOTEN
having count(tgdt.MADT) = (
  select max(SoLuongDT)
  from (
    select count(tgdt2.MADT) as SoLuongDT
    from GIAOVIEN gv2
    join THAMGIADT tgdt2 on gv2.MAGV = tgdt2.MAGV
    join BOMON bm2 on gv2.MABM = bm2.MABM
    where bm2.TENBM = N'Hệ thống thông tin'
    group by gv2.MAGV
  ) as SubQuery
)

--Q56. Cho biết tên giáo viên và tên bộ môn của giáo viên có nhiều người thân nhất.
select gv.HOTEN, bm.TENBM, count(nt.MAGV) as SoLuongNT
from GIAOVIEN gv
join NGUOITHAN nt on gv.MAGV = nt.MAGV
join BOMON bm on gv.MABM = bm.MABM
group by gv.HOTEN, bm.TENBM
having count(nt.MAGV) = (
  select max(SoLuongNT)
  from (
    select count(nt2.MAGV) as SoLuongNT
    from GIAOVIEN gv2
    join NGUOITHAN nt2 on gv2.MAGV = nt2.MAGV
    group by gv2.MAGV
  ) as SubQuery
)

--Q57. Cho biết tên trưởng bộ môn mà chủ nhiệm nhiều đề tài nhất.
select gv.HOTEN, bm.TENBM, count(dt.MADT) as SoLuongDT
from GIAOVIEN gv
join BOMON bm on gv.MAGV = bm.TRUONGBM
join DETAI dt on gv.MAGV = dt.GVCNDT
group by gv.HOTEN, bm.TENBM
having count(dt.MADT) = (
  select max(SoLuongDT)
  from (
    select count(dt2.MADT) as SoLuongDT
    from GIAOVIEN gv2
    join DETAI dt2 on gv2.MAGV = dt2.GVCNDT
    join BOMON bm2 on gv2.MAGV = bm2.TRUONGBM
    group by gv2.MAGV
  ) as SubQuery
)


