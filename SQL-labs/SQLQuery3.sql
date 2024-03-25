CREATE DATABASE leanguage_school_report;






USE [leanguage_school_report]
GO

CREATE TABLE Lessons_report(
	[customer_id] [int] NOT NULL,
	[leanguages] [nvarchar](20) NOT NULL,
	[tests] [nvarchar](20) NULL,
	[rooms] [int] NOT NULL,
CONSTRAINT [PK_dbo_customer2] PRIMARY KEY CLUSTERED(
	[customer_id] ASC
)
) ON [PRIMARY]



USE [leanguage_school_report]
GO
CREATE TABLE Teachers_report(
	[customer_id] [int] NOT NULL,
	[teachers_name] [nvarchar](20) NOT NULL,
	[teachers_age] [int] NOT NULL,
CONSTRAINT [PK_dbo_customer1] PRIMARY KEY CLUSTERED(
	[customer_id] ASC
)
) ON [PRIMARY]






USE [leanguage_school]
GO

CREATE PROCEDURE CopyDataReportDbb
	@KeyColumn int

AS
BEGIN
		INSERT INTO leanguage_school_report.dbo.Lessons_report
		SELECT customer_id,
		leanguages,
		tests,
		rooms
	FROM leanguage_school.dbo.Lessons
	WHERE customer_id > @KeyColumn

		INSERT INTO leanguage_school_report.dbo.Teachers_report
		SELECT customer_id,
		teacher_name,
		teacher_age
	FROM leanguage_school.dbo.Teachers
	WHERE customer_id > @KeyColumn

END
GO





USE leanguage_school_report
Go 
CREATE SYNONYM SynonymCopyDataToReportDbb FOR CopyDataReportDbb
Go





USE leanguage_school
	EXEC CopyDataReportDbb  @KeyColumn = 2





USE leanguage_school_report
	EXEC SynonymCopyDataToReportDbb  @KeyColumn = 2





