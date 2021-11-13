-- query to determine the average rating of all movies released in 2012
SELECT avg(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year == 2012);