--Q1. Cho biết họ tên và mức lương của các giáo viên nữ. 
select HOTEN, LUONG from GIAOVIEN where PHAI=N'Nữ'

--Q2. Cho biết họ tên của các giáo viên và lương của họ sau khi tăng 10%. 
select HOTEN, LUONG * 1.1 as LUONGSAUKHITANG from GIAOVIEN

--Q3. Cho biết mã của các giáo viên có họ tên bắt đầu là “Nguyễn” và lương trên $2000 hoặc giáo viên là trưởng bộ môn nhận chức sau năm 1995. 
select MAGV from GIAOVIEN where HOTEN like N'Nguyễn%' and luong > 2000
union
select TRUONGBM from BOMON where TRUONGBM is not null and NGAYNHANCHUC > '1995-12-31'

--Q4. Cho biết tên những giáo viên khoa Công nghệ thông tin. 
select gv.HOTEN from GIAOVIEN gv
join BOMON bm on gv.MABM=bm.MABM
join KHOA k on bm.MAKHOA=k.MAKHOA 
where k.TENKHOA = N'Công nghệ thông tin'

--Q5. Cho biết thông tin của bộ môn cùng thông tin giảng viên làm trưởng bộ môn đó.
select bm.*, gv.* from BOMON bm
join GIAOVIEN gv on bm.TRUONGBM=gv.MAGV

--Q6. Với mỗi giáo viên, hãy cho biết thông tin của bộ môn mà họ đang làm việc. 
select gv.*, bm.* from GIAOVIEN gv
join BOMON bm on bm.MABM=gv.MABM

--Q7. Cho biết tên đề tài và giáo viên chủ nhiệm đề tài.
select dt.TENDT, gv.HOTEN from DETAI dt
join GIAOVIEN gv on gv.MAGV=dt.GVCNDT

--Q8. Với mỗi khoa cho biết thông tin trưởng khoa. 
select k.*, gv.* from KHOA k
join GIAOVIEN gv on k.TRUONGKHOA=gv.MAGV

--Q9. Cho biết các giáo viên của bộ môn “Vi sinh” có tham gia đề tài 006.
select * from GIAOVIEN
join DETAI on DETAI.GVCNDT=GIAOVIEN.MAGV
where GIAOVIEN.MABM='VS' and DETAI.MADT='006'

--Q10 Với những đề tài thuộc cấp quản lý “Thành phố”, cho biết mã đề tài, đề tài thuộc về chủ đề nào, họ tên người chủ nghiệm đề tài cùng với ngày sinh và địa chỉ của người ấy. 
select dt.MADT, cd.TENCD, gv.HOTEN, gv.NGSINH, gv.DIACHI from DETAI dt
join CHUDE cd on dt.MACD = cd.MACD
join GIAOVIEN gv on dt.GVCNDT = gv.MAGV
where dt.CAPQL = N'Thành phố'

--Q11. Tìm họ tên của từng giáo viên và người phụ trách chuyên môn trực tiếp của giáo viên đó. 
select gv1.HOTEN as GiaoVien, gv2.HOTEN as QuanLyChuyenMon from GIAOVIEN gv1
left join GIAOVIEN gv2 on gv1.GVQLCM = gv2.MAGV

--Q12. Tìm họ tên của những giáo viên được “Nguyễn Thanh Tùng” phụ trách trực tiếp. 
select gv1.HOTEN from GIAOVIEN gv1
join GIAOVIEN gv2 on gv1.GVQLCM = gv2.MAGV
where gv2.HOTEN = N'Nguyễn Thanh Tùng'

--Q13. Cho biết tên giáo viên là trưởng bộ môn “Hệ thống thông tin”.
select gv.HOTEN from GIAOVIEN gv
join BOMON bm on gv.MAGV = bm.TRUONGBM
where bm.TENBM = N'Hệ thống thông tin'

--Q14. Cho biết tên người chủ nhiệm đề tài của những đề tài thuộc chủ đề Quản lý giáo dục. 
select distinct g.HOTEN from GIAOVIEN g
join DETAI dt on g.MAGV = dt.GVCNDT
join CHUDE cd on dt.MACD = cd.MACD
where cd.TENCD = N'Quản lý giáo dục'

--Q15. Cho biết tên các công việc của đề tài HTTT quản lý các trường ĐH có thời gian bắt đầu trong tháng 3/2008. 
select cv.TENCV from CONGVIEC cv
join DETAI dt on cv.MADT = dt.MADT
where dt.TENDT = N'HTTT quản lý các trường ĐH' and MONTH(cv.NGAYBD) = 3 and YEAR(cv.NGAYBD) = 2008


--Q16. Cho biết tên giáo viên và tên người quản lý chuyên môn của giáo viên đó. 
select gv1.HOTEN as GiaoVien, gv2.HOTEN as QuanLyChuyenMon from GIAOVIEN gv1
join GIAOVIEN gv2 on gv1.GVQLCM = gv2.MAGV

--Q17. Cho các công việc bắt đầu trong khoảng từ 01/01/2007 đến 01/08/2007. 
select * from CONGVIEC
where NGAYBD >= '2007-01-01' and NGAYBD <= '2007-08-01'

--Q18. Cho biết họ tên các giáo viên cùng bộ môn với giáo viên “Trần Trà Hương”.
select gv.HOTEN from GIAOVIEN gv
where gv.MABM = (select MABM from GIAOVIEN where HOTEN = N'Trần Trà Hương')
and gv.HOTEN != N'Trần Trà Hương'

--Q19. Tìm những giáo viên vừa là trưởng bộ môn vừa chủ nhiệm đề tài. 
select gv.HOTEN from GIAOVIEN gv
where gv.MAGV in (select TRUONGBM from BOMON where TRUONGBM is not null) 
and gv.MAGV in (select GVCNDT from DETAI)

--Q20. Cho biết tên những giáo viên vừa là trưởng khoa và vừa là trưởng bộ môn. 
select gv.HOTEN from GIAOVIEN gv
where gv.MAGV in (select TRUONGKHOA from KHOA where TRUONGKHOA is not null)
and gv.MAGV in (select TRUONGBM from BOMON where TRUONGBM is not null)

--Q21. Cho biết tên những trưởng bộ môn mà vừa chủ nhiệm đề tài.
select gv.HOTEN from GIAOVIEN gv
where gv.MAGV in (select TRUONGBM from BOMON where TRUONGBM is not null)
and gv.MAGV in (select GVCNDT from DETAI)

--Q22. Cho biết mã số các trưởng khoa có chủ nhiệm đề tài. 
select k.TRUONGKHOA from KHOA k
where k.TRUONGKHOA in (select GVCNDT from DETAI)

--Q23. Cho biết mã số các giáo viên thuộc bộ môn “HTTT” hoặc có tham gia đề tài mã “001”.
select MAGV from GIAOVIEN where MABM = 'HTTT'
union
select MAGV from THAMGIADT where MADT = '001'

--Q24. Cho biết giáo viên làm việc cùng bộ môn với giáo viên 002. 
select gv.HOTEN from GIAOVIEN gv
where gv.MABM = (select MABM from GIAOVIEN where MAGV = '002')
and gv.MAGV != '002'

--Q25. Tìm những giáo viên là trưởng bộ môn. 
select gv.HOTEN from GIAOVIEN gv
where gv.MAGV in (select TRUONGBM from BOMON where TRUONGBM is not null)

--Q26. Cho biết họ tên và mức lương của các giáo viên.
select HOTEN, LUONG from GIAOVIEN