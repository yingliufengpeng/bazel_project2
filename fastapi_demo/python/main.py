import sys
import pandas as pd
print(sys.executable)
print(sys.version_info)


from fastapi import FastAPI

app = FastAPI()

df = pd.DataFrame([[1,2, 3], [4, 5, 6], [7, 8, 9]])

print(df)


@app.get("/")
async def root():
    return {"message": "Hello World"}


