#  Which employee got the largest salary increase since they started working in the company? (display emp_no, salary increase in percentage rounded in 2 decimal places, e.g., 100%)
SELECT emp_no, round(MAX(salary) / MIN(salary)*100,2)-100 AS sal 
FROM salaries 
GROUP BY emp_no ORDER BY sal DESC LIMIT 1;
