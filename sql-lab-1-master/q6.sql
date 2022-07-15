# Display the age of the oldest employee (as an int) in absolute years (assuming they are still working there)
SELECT DISTINCT ABS(ROUND(TIMESTAMPDIFF(MONTH, CURDATE(), birth_date) / 12)) AS years_worked FROM employees WHERE birth_date=
(SELECT MIN(birth_date) FROM employees);
