from fastapi import FastAPI

app = FastAPI(
    title="Athena API",
    description="Backend API for the Athena University Platform",
    version ="0.1.0"
)

@app.get("/")
def root():
    return{
        "message": "welcome to Athena"
    }