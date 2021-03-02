find clean:
	find -name "*.out" -delete
	find -name "*.o" -delete
	find -name depends -delete
find:
	find -name "*.out"
	find -name "*.o"
	find -name depends

git:
	git status
	git add *
	git commit -m"Cpp Class diagram"
	git push
	
