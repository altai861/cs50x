-- Ehleed Kevin Bacon ii toglosn kinonuudin id g oloh ystoi
-- Daraa ni
SELECT name
FROM stars JOIN people ON people.id = stars.person_id
WHERE movie_id IN
(SELECT movie_id
FROM people JOIN stars ON people.id = stars.person_id
WHERE name = 'Kevin Bacon' and birth = 1958);