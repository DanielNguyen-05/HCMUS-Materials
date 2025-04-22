--Họ và tên: Nguyễn Hải Đăng
--MSSV: 23127165
--Lớp: 23CLC03

--a. Cho biết danh sách tất cả giáo viên (magv, hoten) và họ tên giáo viên là quản lý chuyên môn của họ.
select gv1.MAGV, gv1.HOTEN, gv2.HOTEN as HOTEN_GVQLCM
from GIAOVIEN gv1
left join GIAOVIEN gv2 on gv1.MAGV = gv2.GVQLCM

--b. Cho biết danh sách tất cả bộ môn (mabm, tenbm), tên trưởng bộ môn cùng số lượng giáo viên của mỗi bộ môn.
select bm.MABM, bm.TENBM, gv_head.HOTEN as TEN_TRUONGBM, COUNT(gv.MAGV) as SOLUONG_GV  
from BOMON bm
left join GIAOVIEN gv_head on bm.TRUONGBM = gv_head.MAGV 
left join GIAOVIEN gv on bm.MABM = gv.MABM             
group by bm.MABM, bm.TENBM, gv_head.HOTEN 

--c. Cho biết danh sách tất cả các giáo viên nam và thông tin các công việc mà họ đã tham gia.
select gv.MAGV, gv.HOTEN, cv.TENCV
from GIAOVIEN gv
join THAMGIADT tgdt on gv.MAGV = tgdt.MAGV
join CONGVIEC cv on cv.MADT = tgdt.MADT and cv.STT = tgdt.STT
where gv.PHAI = N'Nam'

--d. Cho biết danh sách tất cả các giáo viên và thông tin các công việc thuộc đề tài 001 mà họ tham gia.
select gv.MAGV, gv.HOTEN, cv.TENCV
from GIAOVIEN gv
join THAMGIADT tgdt on gv.MAGV = tgdt.MAGV and tgdt.MADT = '001'
join CONGVIEC cv on cv.MADT = tgdt.MADT and cv.STT = tgdt.STT

-- e. Cho biết thông tin các trưởng bộ môn (magv, hoten) sẽ về hưu vào năm 2014. Biết rằng độ tuổi về hưu của giáo viên nam là 60 còn giáo viên nữ là 55.
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
join BOMON bm on gv.MAGV = bm.TRUONGBM 
where
    (gv.PHAI = N'Nam' and 2014 - YEAR(gv.NGSINH) >= 60) or
    (gv.PHAI = N'Nữ'  and 2014 - YEAR(gv.NGSINH) >= 55);

--f. Cho biết thông tin các trưởng khoa (magv) và năm họ sẽ về hưu.
select gv.MAGV, gv.HOTEN, (case PHAI
						   when N'Nam' then YEAR(gv.NGSINH) + 60
						   when N'Nữ' then YEAR(gv.NGSINH) + 55
						   end) as NAM_VE_HUU
from GIAOVIEN gv
join KHOA kh on gv.MAGV = kh.TRUONGKHOA

--g. Tạo bảng DANHSACHTHIDUA (magv, sodtdat, danhhieu) gồm thông tin mã giáo viên, số đề tài họ tham gia đạt kết quả và danh hiệu thi đua
create table DANHSACHTHIDUA (
    MAGV char(8),           
    SODTDAT int,            
    DANHHIEU nvarchar(50),  
    constraint PK_DANHSACHTHIDUA primary key (MAGV)
)

insert into DANHSACHTHIDUA(MAGV, SODTDAT, DANHHIEU) values
('001', 0, null),
('002', 1, null),
('003', 3, null),
('004', 2, null),
('005', 0, null),
('006', 1, null),
('007', 0, null),
('008', 0, null),
('009', 0, null);

update DANHSACHTHIDUA
set DANHHIEU = (case
				when SODTDAT = 0 then N'Chưa hoàn thành nhiệm vụ'
				when 1 <= SODTDAT AND SODTDAT <= 2 then N'Hoàn thành nhiệm vụ'
				when 3 <= SODTDAT AND SODTDAT <= 5 then N'Tiên tiến'
				when 6 <= SODTDAT then N'Lao động xuất sắc'
				end)

--m. Tổng hợp số lượng các đề tài theo (cấp độ, chủ đề), theo (cấp độ), theo (chủ đề).
select dt.CAPQL, cd.TENCD, COUNT(dt.MADT) as SOLUONG_DETAI
from DETAI dt
join CHUDE cd on dt.MACD = cd.MACD
group by rollup(dt.CAPQL, cd.TENCD)

--n. Tổng hợp mức lương tổng của các giáo viên theo (bộ môn, phái), theo (bộ môn).
select bm.TENBM, gv.PHAI, SUM(gv.LUONG) as TONG_LUONG
from GIAOVIEN gv
join BOMON bm on gv.MABM = bm.MABM
group by rollup(bm.TENBM, gv.PHAI)

--o. Tổng hợp số lượng các giáo viên của khoa CNTT theo (bộ môn, lương), theo (bộ môn), theo (lương).
select bm.TENBM, gv.LUONG, COUNT(gv.MAGV) as SOLUONG_GV
from GIAOVIEN gv
join BOMON bm on gv.MABM = bm.MABM
join KHOA kh on bm.MAKHOA = kh.MAKHOA
where kh.TENKHOA = N'Công nghệ thông tin'
group by rollup(bm.TENBM, gv.LUONG)
