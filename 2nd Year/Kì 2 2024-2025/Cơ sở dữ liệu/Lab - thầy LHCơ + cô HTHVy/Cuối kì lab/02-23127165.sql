-- 02 - H5C6 - 23127165 - Nguyễn Hải Đăng
--Mã đề: 02
--MSSV: 23127165
--Họ và tên: Nguyễn Hải Đăng
--Lớp: 23CLC03
--Vị trí ngồi: H5C6

--1--
select distinct gv.*
from GIAOVIEN gv
join ThAMGIADT tgdt on gv.MAGV = tgdt.MAGV
join DETAI dt on dt.MADT = tgdt.MADT
join CHUDE cd on dt.MACD = cd.MACD
where cd.TENCD = N'Quản lý giáo dục'
go

--2--
select distinct dt.*
from DETAI dt
where not exists (
    select tgdt.MAGV
    from THAMGIADT tgdt
    where tgdt.MADT = dt.MADT
    except
    select gv.MAGV
    from GIAOVIEN gv
    join GV_DT gvdt on gvdt.MAGV = gv.MAGV
    group by gv.MAGV
    having count (distinct gvdt.DIENTHOAI) >= 2
)
and exists (
    select 1
    from THAMGIADT tgdt
    where tgdt.MADT = dt.MADT
)
go

--3--
go
create or alter function fnDem_SLDeTai_Khoa (@MAKHOA char(5), @Thang int, @Nam int)
returns int
as
begin
    declare @cnt int = 0
    select @cnt = count(distinct dt.MADT)
    from DETAI dt
    join GIAOVIEN gv on gv.MAGV = dt.GVCNDT 
    join BOMON bm on bm.MABM = gv.MABM
    join KHOA k on k.MAKHOA = bm.MAKHOA
    where k.MAKHOA = @MAKHOA
    and (
        (month(dt.NGAYBD) = @Thang and year(dt.NGAYBD) = @Nam)
        or
        (month(dt.NGAYKT) = @Thang and year(dt.NGAYKT) = @Nam)
        or
        (dt.NGAYBD <= datefromparts(@Nam, @Thang, 1) and dt.NGAYKT >= dateadd(day, -1, dateadd(month, 1, datefromparts(@Nam, @Thang, 1)))) 
    )
    return @cnt
end
go

--4--
go
create or alter proc spTK_SLDeTai_Khoa (@MAKHOA char(5), @Nam year, @kq int out)
as
begin
    if (@Nam > year(getdate()))
    begin
        print N'Năm không hợp lệ do lớn hơn năm hiện hành'
        set @kq = 0 
        return
    end

    if not exists (select 1 from KHOA k where k.MAKHOA = @MAKHOA)
    begin
        print N'Mã khoa không tồn tại'
        set @kq = 0 
        return
    end

    set @kq = 0

    declare @arr table (
        Thang int,
        SLDT int
    )

    declare @i int = 1
    while (@i <= 12)
    begin
        declare @t int 
        set @t = dbo.fnDem_SLDeTai_Khoa(@MAKHOA, @i, @Nam)
        if (@t > 0)
        begin
            insert into @arr (Thang, SLDT)
            values (@i, @t)
            set @kq = @kq + 1
        end

        set @i = @i + 1
    end 

    select Thang, SLDT
    from @arr
    order by Thang

end 
go 