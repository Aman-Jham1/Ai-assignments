from experta import *


class CareerRecomender(Fact):
    """IT/Reaserch/Management"""
    pass

class Robot(KnowledgeEngine):

    @Rule(CareerRecomender(career='IT'))
    def careerIT(self):
        print("Courses IT")
        print("Hobby club")
        print("CGPA")
        print("Paper pub")
        print("Awards")

    @Rule(CareerRecomender(career='Research'))
    def careerReaserch(self):
        print("Courses Research")
        print("Hobby club")
        print("CGPA")
        print("Paper pub")
        print("Awards")

    @Rule(CareerRecomender(career='Management'))
    def careerManagement(self):
        print("Courses Management")
        print("Hobby club")
        print("CGPA")
        print("Paper pub")
        print("Awards")



engine = Robot()
engine.reset() 
while (True):
    career_option = input("Choose your career options from IT, Research or Management\n")
    engine.declare(CareerRecomender(career=career_option))
    engine.run() 