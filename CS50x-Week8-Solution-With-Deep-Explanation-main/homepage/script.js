document.addEventListener("DOMContentLoaded", () => {
    const addRecommendationBtn = document.getElementById("addRecommendation");
    const recommendationForm = document.getElementById("recommendationForm");
    const submitRecommendationBtn = document.getElementById("submitRecommendation");
    const newRecommendationTextarea = document.getElementById("newRecommendation");

    addRecommendationBtn.addEventListener("click", () => {
        recommendationForm.style.display = "block";
    });

    submitRecommendationBtn.addEventListener("click", () => {
        const newRecommendation = newRecommendationTextarea.value.trim();

        if (newRecommendation) {
            const recommendationsSection = document.getElementById("recommendations");
            const newRecommendationDiv = document.createElement("div");
            newRecommendationDiv.className = "recommendation";
            newRecommendationDiv.innerHTML = `<p>"${newRecommendation}"</p><p>- New Person</p>`;
            recommendationsSection.insertBefore(newRecommendationDiv, recommendationForm);

            newRecommendationTextarea.value = "";
            recommendationForm.style.display = "none";

            alert("Recommendation added successfully!");
        }
    });
});
