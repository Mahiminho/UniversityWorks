
USE leanguage_school
GO

CREATE NONCLUSTERED INDEX leng_id ON Customer
(
    customer_id ASC
) ON [PRIMARY]
GO


CREATE NONCLUSTERED INDEX leng_id ON Lessons
(
    customer_id ASC
) ON [PRIMARY]
GO








