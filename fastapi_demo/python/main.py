import sys
print(sys.executable)
print(sys.version_info)


from fastapi import FastAPI

app = FastAPI()




@app.get("/")
async def root():
    return {"message": "Hello World"}


