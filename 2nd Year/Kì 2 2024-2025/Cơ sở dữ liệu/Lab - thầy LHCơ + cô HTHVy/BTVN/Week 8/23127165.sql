-- Mã số sinh viên: 23127165
-- Họ và tên: Nguyễn Hải Đăng
-- Lớp: 23CLC03

-- a. In ra câu chào “Hello World !!!”.
create procedure DisplayGreeting
as
	begin
		print 'Hello World !!!'
	end
	go
exec DisplayGreeting
go

-- b. In ra tổng 2 số.
create procedure ShowSumTwoNumbers (@num1 float, @num2 float)
as
	begin
		print cast(@num1 + @num2 as nvarchar(50))
	end
	go
exec ShowSumTwoNumbers -1, 2.5
go

-- c. Tính tổng 2 số (sử dụng biến output để lưu kết quả trả về).
create procedure CalculateSumTwoNumbers (@val1 float, @val2 float, @result float out)
as
	begin
		set @result = @val1 + @val2
	end
	go
declare @calc_res float
exec CalculateSumTwoNumbers -1, 2.5, @calc_res out
print cast(@calc_res as nvarchar(50))
go

-- d. In ra tổng 3 số (Sử dụng lại stored procedure Tính tổng 2 số).
create procedure ShowSumThreeNumbers (@v1 float, @v2 float, @v3 float)
as
	begin
		declare @tempSum float
		exec CalculateSumTwoNumbers @v1, @v2, @tempSum out
		declare @finalResult float = @tempSum + @v3
		print cast(@finalResult as nvarchar(50))
	end
	go
exec ShowSumThreeNumbers  1, 2.5, -1
go

-- e. In ra tổng các số nguyên từ m đến n.
create procedure SumIntegersInRange (@startVal float, @endVal float)
as
	begin
		if (@startVal > @endVal)
			begin
				print N'Giá trị không hợp lệ (startVal phải <= endVal)'
				return
			end
		declare @intBegin int
		declare @intEnd int
		if (@startVal - floor(@startVal) <> 0)
			set @intBegin = floor(@startVal) + 1
		else
			set @intBegin = cast(@startVal as int)
		set @intEnd = floor(@endVal)
		if (@intBegin > @intEnd)
			begin
				print N'Không có số nguyên nào.'
				print N'Tổng là: 0'
				return
			end
		declare @rangeSum bigint = 0
		declare	@counter int = @intBegin;
		while (@counter <= @intEnd)
		begin
			set @rangeSum = @rangeSum + @counter
			set @counter = @counter + 1
		end
		print cast(@rangeSum as nvarchar(50))
	end
	go
exec SumIntegersInRange 3.2, 6.25
go

-- f. Kiểm tra 1 số nguyên có phải là số nguyên tố hay không.
create procedure CheckPrimeNumber (@numToCheck int)
as
	begin
		if (@numToCheck < 2)
		begin
			print cast(@numToCheck as nvarchar(20)) + N' không phải là số nguyên tố'
			return
		end
		if (@numToCheck = 2)
		begin
			print cast(@numToCheck as nvarchar(20)) + N' là số nguyên tố'
			return
		end
		if (@numToCheck % 2 = 0)
		begin
			print cast(@numToCheck as nvarchar(20)) + N' không phải là số nguyên tố'
			return
		end
		declare @divisor int = 3;
		while (@divisor * @divisor <= @numToCheck)
			begin
				if (@numToCheck % @divisor = 0)
					begin
						print cast(@numToCheck as nvarchar(20)) + N' không phải là số nguyên tố'
						return
					end
				set @divisor = @divisor + 2
			end
		print cast(@numToCheck as nvarchar(20)) + N' là số nguyên tố'
	end
	go
exec CheckPrimeNumber 29
go

-- g. In ra tổng các số nguyên tố trong đoạn m, n.
create procedure SumPrimesInRange (@lowerBound float, @upperBound float)
as
	begin
		if (@lowerBound > @upperBound)
			begin
				print N'Giới hạn không hợp lệ (lowerBound phải <= upperBound)'
				return
			end
		declare @intStart int
		declare @intFinish int
		if (@lowerBound - floor(@lowerBound) <> 0)
			set @intStart = floor(@lowerBound) + 1
		else
			set @intStart = cast(@lowerBound as int)
		set @intFinish = floor(@upperBound)
		if (@intStart > @intFinish)
			begin
				print N'Không có số nguyên nào.'
				print N'Tổng số nguyên tố là: 0'
				return
			end
		declare @primeTotal bigint = 0;
		declare @currentNum int = @intStart
		while (@currentNum <= @intFinish)
			begin
				if (@currentNum >= 2)
				begin
					declare @isPrimeFlag bit = 1;
					declare @primeDivisor int = 2;
					if (@currentNum = 2)
						set @isPrimeFlag = 1
					else if (@currentNum % 2 = 0)
						set @isPrimeFlag = 0
					else
					begin
						set @primeDivisor = 3
						while (@primeDivisor * @primeDivisor <= @currentNum)
						begin
							if (@currentNum % @primeDivisor = 0)
								begin
									set @isPrimeFlag = 0;
									break
								end
							set @primeDivisor = @primeDivisor + 2
						end
					end
					if (@isPrimeFlag = 1)
					 begin
						set @primeTotal = @primeTotal + @currentNum
					 end
				end
				set @currentNum = @currentNum + 1
			end
			print N'Tổng số nguyên tố: ' + cast(@primeTotal as nvarchar(50))
	end
	go
exec SumPrimesInRange 0, 12
go

-- h. Tính ước chung lớn nhất của 2 số nguyên.
create procedure GetGreatestCommonDivisor (@numA int, @numB int, @gcdResult int out)
as
	begin
		set @numA = ABS(@numA)
		set @numB = ABS(@numB)
		if @numA = 0
		begin
			set @gcdResult = @numB
			return
		end
		if @numB = 0
		begin
			set @gcdResult = @numA
			return
		end
		declare @remainder int
		while (@numB != 0)
			begin
				set @remainder = @numA % @numB
				set @numA = @numB
				set @numB = @remainder
			end
		set @gcdResult = @numA
	end
	go
declare @gcd_val int
exec GetGreatestCommonDivisor 56, 98, @gcd_val out
print @gcd_val
go

-- i. Tính bội chung nhỏ nhất của 2 số nguyên.
create procedure GetLeastCommonMultiple (@intA int, @intB int, @lcmResult bigint out)
as
	begin
		if @intA = 0 or @intB = 0
		begin
			set @lcmResult = 0
			return
		end
		declare @absA bigint = ABS(@intA)
		declare @absB bigint = ABS(@intB)
		declare @gcdVal int
		exec dbo.GetGreatestCommonDivisor @intA, @intB, @gcdVal out
        if (@gcdVal = 0)
            begin
                set @lcmResult = 0;
                return;
            end
        if (@absA % @gcdVal = 0)
            set @lcmResult = (@absA / @gcdVal) * @absB
        else
            set @lcmResult = @absA * (@absB / @gcdVal)
	end
	go
declare @lcm_val bigint
exec GetLeastCommonMultiple 56, 23, @lcm_val out
print @lcm_val
go

-- j. Xuất ra toàn bộ danh sách giáo viên.
create procedure ListAllTeachers
as
	begin
		select *
		from GIAOVIEN
	end
	go
exec ListAllTeachers
go

-- k. Tính số lượng đề tài mà một giáo viên đang thực hiện.
create procedure CountTeacherProjects (@TeacherID char(3))
as
	begin
		if not exists (select 1 from GIAOVIEN where MAGV = @TeacherID)
		begin
			print N'Mã giáo viên không tồn tại: ' + @TeacherID
			return
		end
		select count(distinct tg.MADT)
		from THAMGIADT tg
		where tg.MAGV = @TeacherID
	end
	go
exec CountTeacherProjects '009'
go

-- l. In thông tin chi tiết của một giáo viên(sử dụng lệnh print): Thông tin cá nhân, Số lượng đề tài tham gia, Số lượng thân nhân của giáo viên đó.
create procedure ShowTeacherDetails (@TeacherID char(3))
as
	begin
		if not exists (select 1 from GIAOVIEN where MAGV = @TeacherID)
		begin
			print N'Mã giáo viên không tồn tại: ' + @TeacherID
			return
		end
		declare @fullName nvarchar(100), @salary decimal(10,1), @gender nvarchar(3)
		declare @dob date, @address nvarchar(100), @managerId char(3), @deptId nvarchar(10)
		declare @deptName nvarchar(100)
		declare @managerName nvarchar(100)
		declare @projectCount int, @relativeCount int
		select
			@fullName = gv.HOTEN, @salary = gv.LUONG, @gender = gv.PHAI, @dob = gv.NGAYSINH, @address = gv.DIACHI,
			@managerId = gv.GVQLCM, @deptId = gv.MABM, @deptName = bm.TENBM, @managerName = ql.HOTEN
		from GIAOVIEN gv
		left join BOMON bm on gv.MABM = bm.MABM
		left join GIAOVIEN ql on gv.GVQLCM = ql.MAGV
		where gv.MAGV = @TeacherID
		select @projectCount = count(distinct tg.MADT) from THAMGIADT tg where tg.MAGV = @TeacherID
		select @relativeCount = count(*) from NGUOITHAN tn where tn.MAGV = @TeacherID
		print N'Mã GV: ' + @TeacherID
		print N'Họ Tên: ' + @fullName
		print N'Lương: ' + format(@salary, 'N', 'vi-VN')
		print N'Phái: ' + @gender
		print N'Ngày sinh: ' + convert(nvarchar(10), @dob, 103)
		print N'Địa chỉ: ' + @address
		print N'Mã BM: ' + @deptId + N' (' + isnull(@deptName, 'N/A') + ')'
		print N'GVQLCM: Mã ' + isnull(@managerId, 'N/A') + N' (' + isnull(@managerName, 'Không có') + ')'
		print N'Số đề tài: ' + cast(@projectCount as nvarchar(10))
		print N'Số thân nhân: ' + cast(@relativeCount as nvarchar(10))
	end
	go
exec ShowTeacherDetails '001'
go

-- m. Kiểm tra xem một giáo viên có tồn tại hay không (dựa vào MAGV).
create procedure CheckTeacherExists (@TeacherID char(3))
as
	begin
		if (exists(select 1 from GIAOVIEN gv where gv.MAGV = @TeacherID))
			print N'Giáo viên tồn tại: ' + @TeacherID
		else
			print N'Giáo viên không tồn tại: ' + @TeacherID
	end
	go
exec CheckTeacherExists '001'
go

-- n. Kiểm tra quy định của một giáo viên: Chỉ được thực hiện các đề tài mà bộ môn của giáo viên đó làm chủ nhiệm.
create procedure VerifyProjectAssignmentRule (@TeacherID char(3))
as
	begin
		if not exists (select 1 from GIAOVIEN where MAGV = @TeacherID)
		begin
			print N'Mã giáo viên không tồn tại: ' + @TeacherID
			return
		end
		declare @violationFound bit = 0
		if exists (
			select 1 from THAMGIADT tg
			join DETAI dt on tg.MADT = dt.MADT
			join GIAOVIEN gv_participant on tg.MAGV = gv_participant.MAGV
			join GIAOVIEN gv_leader on dt.GVCNDT = gv_leader.MAGV
			where tg.MAGV = @TeacherID and gv_participant.MABM <> gv_leader.MABM
		) set @violationFound = 1
		if (@violationFound = 1)
			begin
				print N'GV ' + @TeacherID + N' vi phạm quy định.'
			end
		else
			print N'GV ' + @TeacherID + N' tuân thủ quy định.'
	end
	go
exec VerifyProjectAssignmentRule '007'
go

-- o. Thực hiện thêm một phân công cho giáo viên thực hiện một công việc của đề tài: Kiểm tra thông tin đầu vào hợp lệ: giáo viên phải tồn tại, công việc phải tồn tại, thời gian tham gia phải > 0. Kiểm tra quy định ở câu n.
create procedure AddProjectTaskAssignment (
    @TeacherID char(3), @ProjectID char(3), @TaskNo int, @StartDate date, @EndDate date,
    @Allowance float = null, @ResultDesc nvarchar(100) = null
)
as
	begin
		if not exists (select 1 from GIAOVIEN where MAGV = @TeacherID) begin print N'Lỗi: GV không tồn tại.'; return; end
		declare @taskStartDate date, @taskEndDate date
		select @taskStartDate = CV.NGAYBD, @taskEndDate = CV.NGAYKT from CONGVIEC CV where CV.MADT = @ProjectID and CV.STT = @TaskNo
		if (@taskStartDate is null) begin print N'Lỗi: Công việc không tồn tại.'; return; end
        if not exists (select 1 from DETAI where MADT = @ProjectID) begin print N'Lỗi: Đề tài không tồn tại.'; return; end
		if (@StartDate is null or @EndDate is null or @StartDate >= @EndDate) begin print N'Lỗi: Ngày không hợp lệ.'; return; end
        if exists (select 1 from THAMGIADT where MAGV = @TeacherID and MADT = @ProjectID and SOTT = @TaskNo) begin print N'Lỗi: Phân công đã tồn tại.'; return; end
		declare @teacherDept nvarchar(10), @projectDept nvarchar(10)
		select @teacherDept = gv.MABM from GIAOVIEN gv where gv.MAGV = @TeacherID
		select @projectDept = gv_cn.MABM from DETAI dt join GIAOVIEN gv_cn on dt.GVCNDT = gv_cn.MAGV where dt.MADT = @ProjectID
		if (@teacherDept <> @projectDept) begin print N'Lỗi: Vi phạm quy định bộ môn.'; return; end
		begin try
			insert into THAMGIADT(MAGV, MADT, SOTT, NGAYBD, NGAYKT, PHUCAP, KETQUA)
			values (@TeacherID, @ProjectID, @TaskNo, @StartDate, @EndDate, @Allowance, @ResultDesc)
			print N'Thêm phân công thành công.'
		end try
		begin catch
			print N'Lỗi khi thêm: ' + ERROR_MESSAGE()
		end catch
	end
	go
exec AddProjectTaskAssignment '005', '003', 1, '2024-10-01', '2024-12-31'
go

-- p. Thực hiện xoá một giáo viên theo mã. Nếu giáo viên có thông tin liên quan (Có thân nhân, có làm đề tài, ...) thì báo lỗi.
create procedure RemoveTeacher (@TeacherID char(3))
as
	begin
		if not exists (select 1 from GIAOVIEN where MAGV = @TeacherID) begin print N'Lỗi: GV không tồn tại.'; return; end
		if exists (select 1 from THAMGIADT where MAGV = @TeacherID) begin print N'Lỗi: Ràng buộc THAMGIADT.'; return; end
		if exists (select 1 from NGUOITHAN where MAGV = @TeacherID) begin print N'Lỗi: Ràng buộc NGUOITHAN.'; return; end
		if exists (select 1 from DETAI where GVCNDT = @TeacherID) begin print N'Lỗi: Ràng buộc DETAI (GVCNDT).'; return; end
		if exists (select 1 from KHOA where TRUONGKHOA = @TeacherID) begin print N'Lỗi: Ràng buộc KHOA (TRUONGKHOA).'; return; end
		if exists (select 1 from BOMON where TRUONGBM = @TeacherID) begin print N'Lỗi: Ràng buộc BOMON (TRUONGBM).'; return; end
        if exists (select 1 from GIAOVIEN where GVQLCM = @TeacherID) begin print N'Lỗi: Ràng buộc GIAOVIEN (GVQLCM).'; return; end
		begin try
			delete from GIAOVIEN where MAGV = @TeacherID
			print N'Xóa GV thành công: ' + @TeacherID
		end try
		begin catch
			print N'Lỗi khi xóa: ' + ERROR_MESSAGE()
		end catch
	end
	go
go

-- q. In ra danh sách giáo viên của một phòng ban nào đó cùng với số lượng đề tài mà giáo viên tham gia, số thân nhân, số giáo viên mà giáo viên đó quản lý nếu có,...
create procedure ListTeachersByRoom (@RoomNo nvarchar(10))
as
	begin
		if not exists(select 1 from BOMON bm where bm.PHONG = @RoomNo) begin print N'Phòng không tồn tại.'; return; end
		select
			gv.MAGV, gv.HOTEN, gv.MABM,
			(select count(distinct tg.MADT) from THAMGIADT tg where tg.MAGV = gv.MAGV) as ProjectCount,
			(select count(*) from NGUOITHAN tn where tn.MAGV = gv.MAGV) as RelativeCount,
			(select count(*) from GIAOVIEN ql where ql.GVQLCM = gv.MAGV) as ManagedTeacherCount
		 from GIAOVIEN gv
		 join BOMON bm on bm.MABM = gv.MABM
		 where bm.PHONG = @RoomNo
		 order by gv.MAGV
	end
	go
exec ListTeachersByRoom 'B43'
go

-- r. Kiểm tra quy định của 2 giáo viên a, b: Nếu a là trưởng bộ môn c của b thì lương của a phải cao hơn lương của b. (a, b: mã giáo viên)
create procedure VerifyHeadSalaryRule (@HeadTeacherID char(3), @SubordinateTeacherID char(3))
as
	begin
		declare @headName nvarchar(100), @headSalary decimal(10,1)
		declare @subName nvarchar(100), @subSalary decimal(10,1), @subDeptID nvarchar(10)
		declare @actualHeadID char(3)
		select @headName = HOTEN, @headSalary = LUONG from GIAOVIEN where MAGV = @HeadTeacherID
		if (@headName is null) begin print N'Lỗi: GV Trưởng không tồn tại.'; return; end
		select @subName = HOTEN, @subSalary = LUONG, @subDeptID = MABM from GIAOVIEN where MAGV = @SubordinateTeacherID
		if (@subName is null) begin print N'Lỗi: GV cấp dưới không tồn tại.'; return; end
        if (@headSalary is null or @subSalary is null) begin print N'Không thể so sánh lương.'; return; end
		select @actualHeadID = TRUONGBM from BOMON where MABM = @subDeptID
		if (@actualHeadID = @HeadTeacherID)
		begin
			if (@headSalary > @subSalary)
				print N'Quy định OK.'
			else
				print N'Vi phạm quy định lương.'
		end
		else
		begin
			print N'Không phải quan hệ Trưởng BM - GV. Không xét.'
		end
	end
	go
exec VerifyHeadSalaryRule '002', '001'
go

-- s. Thêm một giáo viên: Kiểm tra các quy định: Không trùng tên, tuổi > 18, lương > 0
create procedure AddNewTeacher (
    @TeacherID char(3), @FullName nvarchar(100), @Salary decimal(10, 1), @Gender nvarchar(3),
    @BirthDate date, @Address nvarchar(100), @ManagerID char(3), @DepartmentID nvarchar(10)
)
as
	begin
		if exists (select 1 from GIAOVIEN where MAGV = @TeacherID) begin print N'Lỗi: Mã GV tồn tại.'; return; end
		if exists (select 1 from GIAOVIEN where HOTEN = @FullName) begin print N'Lỗi: Tên GV tồn tại.'; return; end
		if (@Salary <= 0) begin print N'Lỗi: Lương không hợp lệ.'; return; end
		if (@Gender not in (N'Nam', N'Nữ')) begin print N'Lỗi: Phái không hợp lệ.'; return; end
		if (dateadd(year, 18, @BirthDate) > getdate()) begin print N'Lỗi: Tuổi không hợp lệ.'; return; end
		if (@DepartmentID is not null and not exists (select 1 from BOMON where MABM = @DepartmentID)) begin print N'Lỗi: Mã BM không tồn tại.'; return; end
		if (@ManagerID is not null and not exists (select 1 from GIAOVIEN where MAGV = @ManagerID)) begin print N'Lỗi: Mã GVQL không tồn tại.'; return; end
		begin try
			insert into GIAOVIEN(MAGV, HOTEN, LUONG, PHAI, NGAYSINH, DIACHI, GVQLCM, MABM)
			values (@TeacherID, @FullName, @Salary, @Gender, @BirthDate, @Address, @ManagerID, @DepartmentID)
			print N'Thêm GV thành công.'
		end try
		begin catch
			print N'Lỗi khi thêm: ' + ERROR_MESSAGE()
		end catch
	end
	go
exec AddNewTeacher '015', N'Trần Văn Mới', 15500.0 , N'Nam', '1996-05-15', N'111 Đường Mới', '002', 'HTTT'
go

-- t. Mã giáo viên được xác định tự động theo quy tắc: Nếu đã có giáo viên 001, 002, 003 thì MAGV của giáo viên mới sẽ là 004. Nếu đã có giáo viên 001, 002, 005 thì MAGV của giáo viên mới là 003.
create procedure AddTeacherAutoID (
    @FullName nvarchar(100), @Salary decimal(10, 1), @Gender nvarchar(3), @BirthDate date,
    @Address nvarchar(100), @ManagerID char(3), @DepartmentID nvarchar(10)
)
as
	begin
		declare @NewTeacherID char(3), @counter int = 1, @idFound bit = 0;
		while (@idFound = 0)
		begin
			set @NewTeacherID = replace(str(@counter, 3), ' ', '0')
			if not exists (select 1 from GIAOVIEN where MAGV = @NewTeacherID) set @idFound = 1
			else begin set @counter = @counter + 1; if (@counter > 999) begin print N'Lỗi: Hết mã GV.'; return; end end
		end
		if exists (select 1 from GIAOVIEN where HOTEN = @FullName) begin print N'Lỗi: Tên GV tồn tại.'; return; end
		if (@Salary <= 0) begin print N'Lỗi: Lương không hợp lệ.'; return; end
		if (@Gender not in (N'Nam', N'Nữ')) begin print N'Lỗi: Phái không hợp lệ.'; return; end
		if (dateadd(year, 18, @BirthDate) > getdate()) begin print N'Lỗi: Tuổi không hợp lệ.'; return; end
		if (@DepartmentID is not null and not exists (select 1 from BOMON where MABM = @DepartmentID)) begin print N'Lỗi: Mã BM không tồn tại.'; return; end
		if (@ManagerID is not null and not exists (select 1 from GIAOVIEN where MAGV = @ManagerID)) begin print N'Lỗi: Mã GVQL không tồn tại.'; return; end
		begin try
			insert into GIAOVIEN(MAGV, HOTEN, LUONG, PHAI, NGAYSINH, DIACHI, GVQLCM, MABM)
			values (@NewTeacherID, @FullName, @Salary, @Gender, @BirthDate, @Address, @ManagerID, @DepartmentID)
			print N'Thêm GV tự động thành công: ' + @NewTeacherID
		end try
		begin catch
			print N'Lỗi khi thêm tự động: ' + ERROR_MESSAGE()
		end catch
	end
	go
exec AddTeacherAutoID N'Phạm Thị Auto', 20500, N'Nữ', '1986-11-11', N'Địa chỉ auto', '001', 'HTTT'
go